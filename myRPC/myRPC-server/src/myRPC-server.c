#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <libconfig.h>
#include "libmysyslog.h"

#define SETTINGS_PATH "/etc/myRPC/myRPC.conf"
#define USERS_PATH "/etc/myRPC/users.conf"
#define MAX_BUF 2048

#define FALLBACK_DRIVER 0
#define FALLBACK_FORMAT 0
#define FALLBACK_PATH ""

// Проверка, есть ли пользователь в списке разрешённых
int validate_user(const char *login) {
    FILE *f = fopen(USERS_PATH, "r");
    if (!f) {
        dispatch_log_entry("[myRPC-сервер] Не удалось открыть список пользователей", SEVERITY_INFO, FALLBACK_DRIVER, FALLBACK_FORMAT, FALLBACK_PATH);
        return 0;
    }

    char entry[128];
    int found = 0;
    while (fgets(entry, sizeof(entry), f)) {
        entry[strcspn(entry, "\r\n")] = 0;
        if (strcmp(entry, login) == 0) {
            found = 1;
            break;
        }
    }
    fclose(f);
    return found;
}

// Выполняем команду bash и сохраняем вывод
void run_shell_and_capture(const char *cmd, char *out_file, char *err_file) {
    char complete_cmd[1024];
    snprintf(complete_cmd, sizeof(complete_cmd), "%s > %s 2> %s", cmd, out_file, err_file);
    system(complete_cmd);
}

int main() {
    dispatch_log_entry("[myRPC-сервер] Инициализация...", SEVERITY_INFO, FALLBACK_DRIVER, FALLBACK_FORMAT, FALLBACK_PATH);

    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0) {
        dispatch_log_entry("[myRPC-сервер] Ошибка создания сокета", SEVERITY_ERROR, FALLBACK_DRIVER, FALLBACK_FORMAT, FALLBACK_PATH);
        return 1;
    }

    struct sockaddr_in srv_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(1234),
        .sin_addr.s_addr = INADDR_ANY
    };

    if (bind(sock_fd, (struct sockaddr*)&srv_addr, sizeof(srv_addr)) < 0) {
        dispatch_log_entry("[myRPC-сервер] Ошибка привязки порта", SEVERITY_ERROR, FALLBACK_DRIVER, FALLBACK_FORMAT, FALLBACK_PATH);
        return 2;
    }

    char buffer[MAX_BUF];
    while (1) {
        struct sockaddr_in client;
        socklen_t client_len = sizeof(client);
        ssize_t len = recvfrom(sock_fd, buffer, MAX_BUF - 1, 0, (struct sockaddr*)&client, &client_len);
        if (len > 0) {
            buffer[len] = '\0';

            char tmp_out[] = "/tmp/rpc_out_XXXXXX";
            char tmp_err[] = "/tmp/rpc_err_XXXXXX";
            int fd_out = mkstemp(tmp_out), fd_err = mkstemp(tmp_err);
            close(fd_out); close(fd_err);

            run_shell_and_capture(buffer, tmp_out, tmp_err);

            FILE *out_file = fopen(tmp_out, "r");
            char result[MAX_BUF] = {0};
            if (out_file) {
                fread(result, 1, MAX_BUF - 1, out_file);
                fclose(out_file);
            }

            sendto(sock_fd, result, strlen(result), 0, (struct sockaddr*)&client, client_len);
            unlink(tmp_out); unlink(tmp_err);
        }
    }

    close(sock_fd);
    return 0;
}

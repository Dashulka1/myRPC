#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define IO_BUFFER 2048

void usage_hint(const char *program) {
    printf("Применение: %s -s|--stream или -d|--dgram -h <ip_addr> -p <port> -c|--command \"bash команда\"\n", program);
}

int main(int argc, char *argv[]) {
    int protocol_tcp = 1;
    char ip_address[256] = "127.0.0.1";
    int target_port = 1234;
    char shell_command[512] = {0};

    // Обработка аргументов командной строки
    for (int idx = 1; idx < argc; idx++) {
        if (strcmp(argv[idx], "-s") == 0 || strcmp(argv[idx], "--stream") == 0) {
            protocol_tcp = 1;
        } else if (strcmp(argv[idx], "-d") == 0 || strcmp(argv[idx], "--dgram") == 0) {
            protocol_tcp = 0;
        } else if (strcmp(argv[idx], "-h") == 0 || strcmp(argv[idx], "--host") == 0) {
            if (++idx < argc) strncpy(ip_address, argv[idx], sizeof(ip_address) - 1);
            else {
                usage_hint(argv[0]);
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(argv[idx], "-p") == 0 || strcmp(argv[idx], "--port") == 0) {
            if (++idx < argc) target_port = atoi(argv[idx]);
            else {
                usage_hint(argv[0]);
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(argv[idx], "-c") == 0 || strcmp(argv[idx], "--command") == 0) {
            if (++idx < argc) strncpy(shell_command, argv[idx], sizeof(shell_command) - 1);
            else {
                usage_hint(argv[0]);
                exit(EXIT_FAILURE);
            }
        }
    }

    int sock = socket(AF_INET, protocol_tcp ? SOCK_STREAM : SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Ошибка сокета");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(target_port),
        .sin_addr.s_addr = inet_addr(ip_address)
    };

    if (protocol_tcp && connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Ошибка соединения");
        close(sock);
        exit(EXIT_FAILURE);
    }

    sendto(sock, shell_command, strlen(shell_command), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));

    char recv_data[IO_BUFFER] = {0};
    ssize_t received = recvfrom(sock, recv_data, IO_BUFFER - 1, 0, NULL, NULL);
    if (received > 0) {
        recv_data[received] = '\0';
        printf("%s\n", recv_data);
    }

    close(sock);
    return 0;
}

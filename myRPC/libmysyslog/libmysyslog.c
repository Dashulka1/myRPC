#include "libmysyslog.h"
#include <stdio.h>
#include <time.h>
#include <string.h>

// Таблица соответствия уровней логирования
static const char* severity_labels[] = {"DEBUG", "INFO", "WARN", "ERROR", "CRITICAL"};

// Внутренние функции записи в текстовый и JSON-файл
int write_text_log(const char* content, int severity, const char* filepath);
int write_json_log(const char* content, int severity, const char* filepath);

// Главная функция логирования, определяющая драйвер и формат
int dispatch_log_entry(const char* content, int severity, int backend_type, int output_format, const char* filepath) {
    switch (backend_type) {
        case TEXT_DRIVER:
            return write_text_log(content, severity, filepath);
        case JSON_DRIVER:
            return write_json_log(content, severity, filepath);
        default:
            return -1; // Неизвестный драйвер
    }
}

// Запись текстового лога с меткой времени и уровнем
int write_text_log(const char* content, int severity, const char* filepath) {
    FILE* stream = fopen(filepath, "a");
    if (!stream) return -1;

    time_t current_time = time(NULL);
    fprintf(stream, "%ld %s %s\n", current_time, severity_labels[severity], content);
    fclose(stream);

    return 0;
}

// Запись JSON-лога с меткой времени и уровнем
int write_json_log(const char* content, int severity, const char* filepath) {
    FILE* stream = fopen(filepath, "a");
    if (!stream) return -1;

    time_t current_time = time(NULL);
    fprintf(stream, "{\"timestamp\":%ld,\"log_level\":\"%s\",\"message\":\"%s\"}\n", current_time, severity_labels[severity], content);
    fclose(stream);

    return 0;
}

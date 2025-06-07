#ifndef SYSLOG_WRAPPER_H
#define SYSLOG_WRAPPER_H

// Определение уровней важности сообщений
enum SeverityLevel {
    SEVERITY_DEBUG,
    SEVERITY_INFO,
    SEVERITY_WARNING,
    SEVERITY_ERROR,
    SEVERITY_FATAL
};

// Выбор используемого драйвера логирования
enum LogBackend {
    BACKEND_TEXT,
    BACKEND_JSON
};

// Главная функция логирования
int dispatch_log_entry(const char* content, int severity, int backend_type, int output_format, const char* filepath);

#endif // SYSLOG_WRAPPER_H

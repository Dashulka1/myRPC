# Библиотека логирования `libmysyslog`

`libmysyslog` — это модуль на языке C для ведения логов в приложениях. Поддерживаются как текстовые, так и JSON-записи.

## Интерфейс

```c
int dispatch_log_entry(const char* content, int severity, int backend_type, int output_format, const char* filepath);
```

## Уровни логирования

- `DEBUG`
- `INFO`
- `WARNING`
- `ERROR`
- `FATAL`

## Поддерживаемые форматы

### Текстовый

```
<timestamp> <log_level> <сообщение>
```

### JSON

```json
{
  "timestamp": 1720000000,
  "log_level": "ERROR",
  "message": "example"
}
```

## Сборка

```bash
cd libmysyslog
make все
make deb
```
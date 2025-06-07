# myRPC-клиент

`myRPC-client` — это утилита командной строки, позволяющая отправлять команды на сервер и получать результаты их выполнения.

## Сборка

```bash
cd myRPC-client
make все
```

## Использование

```bash
./myRPC-client -s|--stream | -d|--dgram \
               -h <IP-сервера> \
               -p <порт> \
               -c|--command "bash-команда"
```

## Аргументы

- `-s`, `--stream`: использовать TCP
- `-d`, `--dgram`: использовать UDP
- `-h`, `--host`: IP-адрес сервера
- `-p`, `--port`: порт
- `-c`, `--command`: исполняемая команда

## Примеры

```bash
./myRPC-client --stream --host 192.168.1.1 --port 1234 --command "ls /tmp"
./myRPC-client -d -h 10.0.0.5 -p 4321 -c "df -h"
```
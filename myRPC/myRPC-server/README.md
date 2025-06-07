# Сервер myRPC

`myRPC-server` — это демон, который принимает команды по сети, исполняет их и возвращает результат клиенту.

## Зависимости

- GCC
- `libconfig-dev`
- `pkg-config`
- `libmysyslog`

```bash
sudo apt update
sudo apt install -y gcc make libconfig-dev pkg-config
```

## Сборка

```bash
cd myRPC-server
make все
```

## Настройка

1. Создайте директорию конфигурации:

   ```bash
   sudo mkdir -p /etc/myRPC
   ```

2. Пример `/etc/myRPC/myRPC.conf`:

   ```conf
   port = 1234;
   socket_type = "stream";  # или "dgram"
   ```

3. Пример `/etc/myRPC/users.conf`:

   ```
   alice
   bob
   ```

## Запуск вручную

```bash
sudo ./myRPC-server
```

## Запуск через systemd

```bash
sudo systemctl start myrpc-server
```

## Сборка .deb-пакета

```bash
make deb
```
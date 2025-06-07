CC = gcc
CFLAGS = -Wall -O2

SRC = src/myRPC-client.c
OBJ = myRPC-client.o
BIN = myRPC-client

version = 1.0
revision = 0
architecture = all

.PHONY: все clean deb

все: $(BIN)

$(OBJ): $(SRC)
  $(CC) $(CFLAGS) -c $< -o $@

$(BIN): $(OBJ)
  $(CC) $(CFLAGS) -o $@ $^

deb:
  mkdir -p MyClient_$(version)-$(revision)_$(architecture)/DEBIAN
  printf "Package: myrpc-client\nVersion: $(version)\nArchitecture: $(architecture)\nDepends: libmysyslog\nMaintainer: example <dev@example.com>\nDescription: Клиентская утилита для удалённого выполнения команд\n" \
    > MyClient_$(version)-$(revision)_$(architecture)/DEBIAN/control
  mkdir -p MyClient_$(version)-$(revision)_$(architecture)/usr/local/bin
  cp $(BIN) MyClient_$(version)-$(revision)_$(architecture)/usr/local/bin
  dpkg-deb --build MyClient_$(version)-$(revision)_$(architecture)

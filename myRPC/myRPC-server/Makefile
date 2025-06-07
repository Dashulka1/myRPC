CC = gcc
PKG_CONFIG = pkg-config

CONFIG_CFLAGS  = $(shell $(PKG_CONFIG) --cflags libconfig)
CONFIG_LDFLAGS = $(shell $(PKG_CONFIG) --libs libconfig)

LIBDIR = ../libmysyslog

CFLAGS = -Wall -O2 -I$(LIBDIR) $(CONFIG_CFLAGS)
LDFLAGS = -L$(LIBDIR) -lmysyslog $(CONFIG_LDFLAGS)

SRC = src/myRPC-server.c
OBJ = myRPC-server.o
BIN = myRPC-server

version = 1.0
revision = 0
architecture = all

.PHONY: все clean deb

все: $(BIN)

$(OBJ): $(SRC)
  $(CC) $(CFLAGS) -c $< -o $@

$(BIN): $(OBJ)
  $(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

deb:
  mkdir -p MyServer_$(version)-$(revision)_$(architecture)/DEBIAN
  printf "Package: myrpc-server\nVersion: $(version)\nArchitecture: $(architecture)\nDepends: libmysyslog, libconfig-dev\nMaintainer: example <dev@example.com>\nDescription: Серверная служба myRPC\n" \
    > MyServer_$(version)-$(revision)_$(architecture)/DEBIAN/control
  mkdir -p MyServer_$(version)-$(revision)_$(architecture)/usr/local/sbin
  cp $(BIN) MyServer_$(version)-$(revision)_$(architecture)/usr/local/sbin
  dpkg-deb --build MyServer_$(version)-$(revision)_$(architecture)

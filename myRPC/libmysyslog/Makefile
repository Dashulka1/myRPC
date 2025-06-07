CC = gcc
CFLAGS = -Wall -O2 -fPIC

SRC = libmysyslog.c
OBJ = libmysyslog.o
STATIC = libmysyslog.a
SHARED = libmysyslog.so

version     = 1.0
revision    = 0
architecture = all

.PHONY: все clean deb

все: $(STATIC) $(SHARED)

$(OBJ): $(SRC)
  $(CC) $(CFLAGS) -c $< -o $@

$(STATIC): $(OBJ)
  ar rcs $@ $^

$(SHARED): $(OBJ)
  $(CC) -shared -o $@ $^

deb:
  mkdir -p MySyslog_$(version)-$(revision)_$(architecture)/DEBIAN
  printf "Package: libmysyslog\nVersion: $(version)\nArchitecture: $(architecture)\nMaintainer: example <dev@example.com>\nDescription: Расширяемая библиотека логирования\n" \
    > MySyslog_$(version)-$(revision)_$(architecture)/DEBIAN/control
  mkdir -p MySyslog_$(version)-$(revision)_$(architecture)/usr/local/lib
  mkdir -p MySyslog_$(version)-$(revision)_$(architecture)/usr/local/include
  cp $(STATIC) MySyslog_$(version)-$(revision)_$(architecture)/usr/local/lib
  cp libmysyslog.h MySyslog_$(version)-$(revision)_$(architecture)/usr/local/include
  dpkg-deb --build MySyslog_$(version)-$(revision)_$(architecture)

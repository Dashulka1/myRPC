.PHONY: все очистить сборка deb-архив репозиторий установить-службу

все: очистить
  $(MAKE) -C libmysyslog все
  $(MAKE) -C myRPC-client все
  $(MAKE) -C myRPC-server все

очистить:
  $(MAKE) -C libmysyslog clean
  $(MAKE) -C myRPC-client clean
  $(MAKE) -C myRPC-server clean
  rm -f *.deb

deb-архив: все
  $(MAKE) -C libmysyslog deb
  $(MAKE) -C myRPC-client deb
  $(MAKE) -C myRPC-server deb
  mv libmysyslog/*.deb .
  mv myRPC-client/*.deb .
  mv myRPC-server/*.deb .

репозиторий: deb-архив
  mkdir -p /usr/local/repos
  cp *.deb /usr/local/repos
  cd /usr/local/repos && dpkg-scanpackages . /dev/null | gzip -9c > Packages.gz
  echo "deb [trusted=yes] file:/usr/local/repos ./" | sudo tee /etc/apt/sources.list.d/myrpc.list
  sudo apt-get update

установить-службу:
  sudo cp systemd/myrpc-server.service /etc/systemd/system/
  sudo systemctl daemon-reload

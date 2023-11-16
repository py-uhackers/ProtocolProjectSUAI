#!/bin/bash

# Генерируем 4000 символов
data=$(LC_ALL=C tr -dc 'a-zA-Z0-9' < /dev/urandom | fold -w 4000 | head -n 1)

# Указываем адрес и порт сервера UDP
udp_server="192.168.31.237"
udp_port="10001"

# Отправляем данные по UDP
echo -n "$data" | nc -u -w 1 $udp_server $udp_port

echo "Данные отправлены по UDP."


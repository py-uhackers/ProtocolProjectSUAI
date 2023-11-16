#!/bin/bash

# Генерируем 4000 символов
data=$(LC_ALL=C tr -dc 'a-zA-Z0-9' < /dev/urandom | fold -w 3000 | head -n 1)

# Указываем адрес и порт сервера TCP
tcp_server="192.168.31.237"
tcp_port="10000"

if ! nc -z "$tcp_server" "$tcp_port"; then
  echo "Ошибка: Невозможно подключиться к серверу $tcp_server:$tcp_port"
  exit 1
fi

# Отправляем данные по TCP с помощью telnet
(echo -n "$data"; sleep 1) | telnet $tcp_server $tcp_port

echo "Данные отправлены по TCP."

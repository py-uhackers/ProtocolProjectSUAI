#include <WiFi.h>
#include <WiFiUdp.h>

const char *ssid = "Adidas-room230";
const char *password = "2589625896";

WiFiUDP udp;

void setup() {
  Serial.begin(115200);

  // Подключение к Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Подключение к WiFi...");
  }
  Serial.println("Подключено к Wi-Fi");

  // Настройка UDP
  udp.begin(1234);  // Порт для отправки данных
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();
    if (input == '5') {
      sendUDPData();
    }
  }
}

void sendUDPData() {
  // IP-адрес и порт для отправки UDP-пакета
  IPAddress remoteIP(192, 168, 31, 237);  // Замените на IP-адрес вашего сервера
  uint16_t remotePort = 10001;            // Замените на порт вашего сервера

  // Создание строки данных для отправки (4000 символов)
  String sendData = "";
  for (int i = 0; i < 4000; i++) {
    sendData += "A";
  }

  // Отправка данных по UDP
  udp.beginPacket(remoteIP, remotePort);
  udp.print(sendData);
  udp.endPacket();

  Serial.println("Данные отправлены по UDP");
}

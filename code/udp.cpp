#include <Arduino.h>
#include "WiFi.h"

#define WIFI_SSID "NEO"
#define WIFI_PASSWORD "54332232"

const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;

const int port = 10000;
WiFiUDP udp;
const int udpPort = 10001;

String translateEncryptionType(wifi_auth_mode_t encryptionType)
{
  switch (encryptionType)
  {
  case (WIFI_AUTH_OPEN):
    return "Open";
  case (WIFI_AUTH_WEP):
    return "WEP";
  case (WIFI_AUTH_WPA_PSK):
    return "WPA_PSK";
  case (WIFI_AUTH_WPA2_PSK):
    return "WPA2_PSK";
  case (WIFI_AUTH_WPA_WPA2_PSK):
    return "WPA_WPA2_PSK";
  case (WIFI_AUTH_WPA2_ENTERPRISE):
    return "WPA2_ENTERPRISE";
  default:
    return "UNKNOWN";
  }
  return "UNKNOWN";
}

void scanNetworks()
{
  int numberOfNetworks = WiFi.scanNetworks();
  Serial.print("Number of networks found: ");
  Serial.println(numberOfNetworks);

  for (int i = 0; i < numberOfNetworks; i++)
  {
    Serial.print("Network name: ");
    Serial.println(WiFi.SSID(i));

    Serial.print("Signal strength: ");
    Serial.println(WiFi.RSSI(i));

    Serial.print("MAC address: ");
    Serial.println(WiFi.BSSIDstr(i));

    Serial.print("Encryption type: ");
    String encryptionTypeDescription = translateEncryptionType(WiFi.encryptionType(i));
    Serial.println(encryptionTypeDescription);
    Serial.println("-----------------------");
  }
}

void connectToNetwork()
{
  WiFi.begin(ssid, password);
  Serial.println("!!!");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Establishing connection to WiFi..");
  }

  Serial.println("Connected to network");
}

void handleUDPClient()
{
  int packetSize = udp.parsePacket();
  if (packetSize)
  {
    Serial.println(packetSize);
    uint8_t data[packetSize];
    udp.read(data, packetSize);

    data[packetSize - 1] = '\0';

    Serial.print("Client sent: ");
    Serial.println((char *)data);
  }
}

void setup()
{
  Serial.begin(115200);

  scanNetworks();
  connectToNetwork();

  Serial.println(WiFi.macAddress());
  Serial.println(WiFi.localIP());

  udp.begin(udpPort);
}

void loop()
{
  handleUDPClient();
  delay(10);
}
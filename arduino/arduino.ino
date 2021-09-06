#include "DHT.h"
#include <ESP8266WiFi.h>

#define DHTPIN 14     
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;
const char* ssid     = "TieuThon";
const char* password = "thoaideptrai";
const char* server = "192.168.43.143";
const int port = 8080;

void setup() {
  Serial.begin(9600);
  dht.begin();

  Serial.println();
  Serial.println();
  Serial.print("Đang kết nối đến ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi đã kết nối");
}

void loop() {
  delay(6000);

  float humi = dht.readHumidity();
  float temp = dht.readTemperature();

  if (isnan(humi) || isnan(temp)) {
    Serial.println("Không đọc được dữ liệu từ cảm biến DHT11!");
    return;
  }

  if (client.connect(server, port)) {
    String request = "/update?temp=" + String(temp) + "&humi=" + String(humi);
    client.print("GET " + request + " HTTP/1.1\n" + "Host: "+ server +"\n" + "Connection: close\n" + "Content-Length: 0\n" +"\n\n"); 
    
    Serial.println("Nhiệt Độ: " + String(temp) + "°C Độ Ẩm: " + String(humi) + "%");
  }else{
    Serial.println("Không thể kết nối đến server!");
  }
  client.stop(); 
}

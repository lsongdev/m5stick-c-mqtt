#include <M5StickC.h>
#include <WiFi.h>
#include <PubSubClient.h>

// WiFi 设置
const char* ssid = "wifi@lsong.one";
const char* password = "song940@163.com";

// MQTT Broker 设置
const char* mqtt_server = "192.168.2.100";
const int mqtt_port = 1883;
const char* mqtt_topic = "esp8266-relay-220v";

WiFiClient espClient;
PubSubClient client(espClient);
bool buttonState = false;

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("m5stick")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(2);
  
  Serial.println("Connecting to WiFi...");
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  M5.update();
  if (M5.BtnA.wasPressed()) {
    buttonState = !buttonState;
    
    if (buttonState) {
      client.publish(mqtt_topic, "relay1on");
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(10, 30);
      M5.Lcd.print("Status: ON");
    } else {
      client.publish(mqtt_topic, "relay1off");
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(10, 30);
      M5.Lcd.print("Status: OFF");
    }
  }
  delay(100);
}
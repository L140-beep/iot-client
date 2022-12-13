#include "WiFi.h"
#include "Server.h"
#include "MQTT.h"
#include "Led.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial(5,4); //RX, TX

String inputData = "";

void setup() {
  Serial.begin(9600);
  WiFi_init(false);
  MQTT_init();
  mqtt_cli.publish((mqtt_client_id + "/state").c_str(), "hello");
  mySerial.begin(4800);
}

void loop() {  
  mqtt_cli.loop();

  char ch;
  while (mySerial.available()) {
    ch = (char)mySerial.read();
    if (ch == '\n'){
      mqtt_cli.publish((mqtt_client_id + "/DATA").c_str(), String(inputData).c_str());
      Serial.println(inputData);
      inputData = "";
      delay(1000);
      break;
    }
    
    inputData += ch;
  }
}

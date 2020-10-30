#include <Arduino.h>
#include "setup.h"

void setup() {
  Serial.begin(115200);
  Serial.println(F("Power monitor (version 1.2.0"));
  Serial.println(F("\tInitializing INA-219 sensor..."));
  ina219_sensor.begin();
  Serial.println(F("\tInitiating TFT..."));
  tft.reset();
  tft_id = tft.readID();
  Serial.print(F("\tTFT identifier: 0x"));
  Serial.println(String(tft_id, HEX));
  tft.begin(tft_id);
  tft.fillScreen(BLACK);
  tft.setRotation(1);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(150,10);
  tft.println("Power Monitor");
  tft.setTextSize(1);
  tft.setCursor(200,30);
  tft.println("(version 1.2.0)");
  tft.setCursor(320,305);
  tft.println("developed by Robson Costa");
}

void loop() {
  // put your main code here, to run repeatedly:
}
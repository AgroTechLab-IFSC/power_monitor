#include <Arduino.h>
#include "setup.h"

/**
 * @fn setup
 * @brief Configure all parameters before call loop function.
 */
void setup() {
  // Initialize sensor values
  sensor_values.count = 0;
  sensor_values.actual_voltage = 0.0f;
  sensor_values.min_voltage = __FLT_MAX__;
  sensor_values.max_voltage = __FLT_MIN__;
  sensor_values.avg_voltage = 0.0f;
  sensor_values.sum_voltage = 0.0f;
  sensor_values.actual_current = 0.0f;
  sensor_values.min_current = __FLT_MAX__;
  sensor_values.max_current = __FLT_MIN__;
  sensor_values.avg_current = 0.0f;
  sensor_values.sum_current = 0.0f;

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
  tft.setCursor(165,10);
  tft.println("Power Monitor");
  tft.setTextSize(1);
  tft.setCursor(200,30);
  tft.println("(version 1.2.0)");
  tft.setCursor(318,310);
  tft.println("by AgroTechLab (IFSC/Lages)");
  tft.setTextColor(YELLOW);
  tft.setCursor(20,15);
  tft.println("Sampling Interval");
  tft.setCursor(55,25);
  tft.println(SAMPLE_INTERVAL);
  tft.setCursor(75,25);
  tft.println("ms");
  tft.setCursor(370,15);
  tft.println("Showing Interval");
  tft.setCursor(405,25);
  tft.println(SHOW_INTERVAL);
  tft.setCursor(430,25);
  tft.println("ms");

  tft.setTextColor(WHITE);
  tft.setTextSize(2);    
  tft.setCursor(15, 60);
  tft.println("Sampled count..............:");
  tft.setCursor(360, 60);
  tft.println(sensor_values.count);

  tft.setCursor(15, 95);
  tft.println("Actual voltage (V).........:");
  tft.setCursor(360, 95);
  tft.println(sensor_values.actual_voltage);
  tft.setTextColor(GREEN);
  tft.setCursor(50, 120);
  tft.println("Avg voltage (V).........:");
  tft.setCursor(360, 120);
  tft.println(sensor_values.avg_voltage);
  tft.setTextColor(BLUE);
  tft.setCursor(50, 145);
  tft.println("Min voltage (V).........:");
  tft.setCursor(360, 145);
  tft.println(sensor_values.min_voltage);
  tft.setTextColor(RED);
  tft.setCursor(50, 170);
  tft.println("Max voltage (V).........:");
  tft.setCursor(360, 170);
  tft.println(sensor_values.max_voltage);

  tft.setTextColor(WHITE);
  tft.setCursor(15, 205);
  tft.println("Actual current (mA)........:");
  tft.setCursor(360, 205);
  tft.println(sensor_values.actual_current);
  tft.setTextColor(GREEN);
  tft.setCursor(50, 230);
  tft.println("Avg current (mA)........:");
  tft.setCursor(360, 230);
  tft.println(sensor_values.avg_current);
  tft.setTextColor(BLUE);
  tft.setCursor(50, 255);
  tft.println("Min current (mA)........:");
  tft.setCursor(360, 255);
  tft.println(sensor_values.min_current);
  tft.setTextColor(RED);
  tft.setCursor(50, 280);
  tft.println("Max current (mA)........:");    
  tft.setCursor(360, 280);
  tft.println(sensor_values.max_current);
}

/**
 * @fn loop
 * @brief Loop function executed cyclically.
 */
void loop() {
  // Check if its time to sample
  if ((millis() - last_sample) >= SAMPLE_INTERVAL) {
    last_sample = millis();
    sensor_values.count++;
    sensor_values.actual_voltage = ina219_sensor.getBusVoltage_V();
    if (sensor_values.actual_voltage < sensor_values.min_voltage) {
      sensor_values.min_voltage = sensor_values.actual_voltage;
    }
    if (sensor_values.actual_voltage > sensor_values.max_voltage) {
      sensor_values.max_voltage = sensor_values.actual_voltage;
    }
    sensor_values.sum_voltage += sensor_values.actual_voltage;
    sensor_values.avg_voltage = sensor_values.sum_voltage/sensor_values.count;
    sensor_values.actual_current = ina219_sensor.getCurrent_mA();
    if ((sensor_values.actual_current >= 0.0f) && (sensor_values.actual_current < sensor_values.min_current)) {
      sensor_values.min_current = sensor_values.actual_current;
    }
    if ((sensor_values.actual_current >= 0.0f) && (sensor_values.actual_current > sensor_values.max_current)) {
      sensor_values.max_current = sensor_values.actual_current;
    }
    sensor_values.sum_current += sensor_values.actual_current;
    sensor_values.avg_current = sensor_values.sum_current/sensor_values.count;
  }

  // Check if its time to show
  if ((millis() - last_show) >= SHOW_INTERVAL) {
    last_show = millis();
    
    tft.fillRoundRect(355, 55, 90, 25, 5, BLACK);
    tft.setTextColor(WHITE);
    tft.setCursor(360, 60);
    tft.println(sensor_values.count);

    tft.fillRoundRect(355, 90, 70, 25, 5, BLACK);
    tft.setTextColor(WHITE);
    tft.setCursor(360, 95);
    tft.println(sensor_values.actual_voltage);
    tft.fillRoundRect(355, 115, 70, 25, 5, BLACK);
    tft.setTextColor(GREEN);
    tft.setCursor(360, 120);
    tft.println(sensor_values.avg_voltage);
    tft.fillRoundRect(355, 140, 70, 25, 5, BLACK);
    tft.setTextColor(BLUE);
    tft.setCursor(360, 145);
    tft.println(sensor_values.min_voltage);
    tft.fillRoundRect(355, 165, 70, 25, 5, BLACK);
    tft.setTextColor(RED);
    tft.setCursor(360, 170);
    tft.println(sensor_values.max_voltage);

    tft.fillRoundRect(355, 200, 70, 25, 5, BLACK);
    tft.setTextColor(WHITE);
    tft.setCursor(360, 205);
    tft.println(sensor_values.actual_current);
    tft.fillRoundRect(355, 225, 70, 25, 5, BLACK);
    tft.setTextColor(GREEN);
    tft.setCursor(360, 230);
    tft.println(sensor_values.avg_current);
    tft.fillRoundRect(355, 250, 70, 25, 5, BLACK);
    tft.setTextColor(BLUE);
    tft.setCursor(360, 255);
    tft.println(sensor_values.min_current);
    tft.fillRoundRect(355, 275, 70, 25, 5, BLACK);
    tft.setTextColor(RED);
    tft.setCursor(360, 280);
    tft.println(sensor_values.max_current);
  }
}
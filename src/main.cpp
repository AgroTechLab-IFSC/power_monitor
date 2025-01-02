/**
 * @mainpage
 * The Power Monitor aims to get data about the energy consumption of IoT devices.<br>
 * Actual, average, minimum and maximum values are sampled at each 50 ms.<br>
 * This values are updated at each 3 seconds on LCD interface.<br>
 * It provides the following information:
 * \li Actual voltage (in V);
 * \li Average voltage (in V);
 * \li Minimal voltage (in V);
 * \li Maximum voltage (in V);
 * \li Actual current (in mA);
 * \li Average current (in mA);
 * \li Minimal current (in mA);
 * \li Maximum current (in mA);
 * 
 * ![PowerMonitor](../figs/powermonitor_display.jpg)<br>
 * 
 * <br>The <b>hardware requirements</b> are:
 * \li \subpage mega_2560_page - microcontroller;
 * \li \subpage lcd_page - display;
 * \li \subpage ina219_page - energy sensor;
 */

/**
 * \page mega_2560_page Arduino MEGA 2560 
 * The Arduino Mega 2560 is a microcontroller board based on the ATmega2560. It has 54 digital input/output pins 
 * (of which 15 can be used as PWM outputs), 16 analog inputs, 4 UARTs (hardware serial ports), a 16 MHz crystal 
 * oscillator, a USB connection, a power jack, an ICSP header, and a reset button. It contains everything needed to 
 * support the microcontroller; simply connect it to a computer with a USB cable or power it with a AC-to-DC adapter 
 * or battery to get started. The Mega 2560 board is compatible with most shields designed for the Uno and the former 
 * boards Duemilanove or Diecimila.
 * 
 * Key features are listed below, hardware details can be found into [datasheet](mega2560.pdf):
 * - Supply voltage (recommended): 7V ~ 12V;
 * - Supply voltage (limits): 6V ~ 20V;
 * - Operating voltage: 5V;
 * - Microcontroller: ATmega2560;
 * - Digital I/O pins: 54 (of which 15 provide PWM output);
 * - Analog input pins: 16;
 * - DC Current per I/O Pin: 20 mA;
 * - DC Current for 3.3V Pin: 50 mA;
 * - Flash memory: 256Kb (8Kb used by bootloader);
 * - SRAM: 8Kb;
 * - EEPROM: 4Kb;
 * - CPU clock: 16MHz;
 * 
 * ![MEGA2560](mega2560.jpg)<br>
 * ![MEGA2560 pinout](mega2560_pinout.png)
 */

/**
 * \page lcd_page 3,5'' TFT LCD
 * The 3,5'' TFT LCD shield is a display with 262.000 colours, 480x320 pixels of resolution and touchscreen.
 * 
 * Key features are listed below:
 * - Supply voltage 3.3V ~ 5V;
 * - 480x320 resolution;
 * - 262.000 colours;
 * - TFT LCD (<i>Thin Film Transistor Liquid Crystal Display</i>);
 * - Resistive touchscreen;
 * - LED backlight;
 * - With SD card slot;
 * - Arduino and STM32 compatible;
 * 
 * ![LCD schematic connection](lcd1.jpg)
 * ![LCD schematic connection](lcd2.jpg)
 */

/**
 * \page ina219_page INA-219
 * The INA219 is a current shunt and power monitor with an I2C- or SMBUS-compatible interface. The device monitors
 * both shunt voltage drop and bus supply voltage, with programmable conversion times and filtering. A programmable 
 * calibration value, combined with an internal multiplier, enables direct readouts of current in amperes. An additional
 * multiplying register calculates power in watts. The I2C- or SMBUS-compatible interface features 16 programmable addresses. 
 *  
 * Key features are listed below, hardware details can be found into [datasheet](ina219.pdf):
 * - Supply voltage 3V ~ 5.5V;
 * - Operating temperature range -40ºC to 125ºC;
 * - Senses Bus Voltages from 0 to 26 V;
 * - 12 bits resolution;
 * - Reports Current, Voltage, and Power;
 * - 16 Programmable Addresses;
 * - Filtering Options;
 * - Calibration Registers;
 * 
 * ![INA219 pinout](ina219.jpg)
 */ 

/** 
 * @file main.cpp
 * @author Robson Costa (robson.costa@ifsc.edu.br)
 * @brief Project main file.
 * @version 1.3.0
 * @since 30/10/2020 
 * @date 02/01/2025
 * 
 * @copyright Copyright (c) since 2020 - AgroTechLab. \n
 * Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International Unported License (the <em>"License"</em>). You may not
 * use this file except in compliance with the License. You may obtain a copy of the License <a href="https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode" target="_blank">here</a>.
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an <em>"as is" basis, 
 * without warranties or  conditions of any kind</em>, either express or implied. See the License for the specific language governing permissions 
 * and limitations under the License.
 */
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
#ifndef __SETUP_H__
#define __SETUP_H__

#include <Wire.h>
#include <Adafruit_INA219.h>
#include "MCUFRIEND_kbv.h"
#include "Adafruit_GFX.h"
#include "TouchScreen.h"

// Colors definition
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

// TFT definitions
#define MINPRESSURE 200
#define MAXPRESSURE 1000
const int XP=6,XM=56,YP=55,YM=7; //ID=0x9486

// INA-219 address
#define INA219_ADDR   0x40

// Systema definitions
#define SAMPLE_INTERVAL   200
#define SHOW_INTERVAL     1000

struct electric_monitor {
  uint32_t count;
  float actual_voltage;
  float min_voltage;
  float max_voltage;
  float avg_voltage;
  float sum_voltage;
  float actual_current;
  float min_current;
  float max_current;
  float avg_current;
  float sum_current;
};

// Global variables
Adafruit_INA219 ina219_sensor = Adafruit_INA219(INA219_ADDR);
MCUFRIEND_kbv tft;
electric_monitor sensor_values;
uint16_t tft_id = 0;
uint64_t last_sample = 0;
uint64_t last_show = 0;

#endif
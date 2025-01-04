#ifndef __SETUP_H__
#define __SETUP_H__

#include <Wire.h>
#include <Adafruit_INA219.h>
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include <TouchScreen.h>

/**
 * \def BLACK 
 * TFT black color.
 */
#define BLACK   0x0000

/**
 * \def BLUE 
 * TFT blue color.
 */
#define BLUE    0x001F

/**
 * \def RED 
 * TFT red color.
 */
#define RED     0xF800

/**
 * \def GREEN 
 * TFT green color.
 */
#define GREEN   0x07E0

/**
 * \def CYAN 
 * TFT cyan color.
 */
#define CYAN    0x07FF

/**
 * \def MAGENTA 
 * TFT magenta color.
 */
#define MAGENTA 0xF81F

/**
 * \def YELLOW 
 * TFT yellow color.
 */
#define YELLOW  0xFFE0

/**
 * \def WHITE 
 * TFT white color.
 */
#define WHITE   0xFFFF

/**
 * \def MINPRESSURE 
 * TFT minimal pressure.
 */
#define MINPRESSURE 200

/**
 * \def MAXPRESSURE 
 * TFT maximum pressure.
 */
#define MAXPRESSURE 1000

/**
 * \def XP
 * Pinout of X+.
 */
#define XP 6

/**
 * \def XM
 * Pinout of X-.
 */
#define XM 56

/**
 * \def YP
 * Pinout of Y+.
 */
#define YP 55

/**
 * \def YM
 * Pinout of Y-.
 */
#define YM 7

//ID=0x9486

/**
 * \def INA219_ADDR 
 * INA-219 I2C address.
 */
#define INA219_ADDR   0x40

/**
 * \def SAMPLE_INTERVAL 
 * INA-219 sampling interval (in ms).
 */
#define SAMPLE_INTERVAL   50

/**
 * \def SHOW_INTERVAL 
 * LCD showing interval (in ms).
 */
#define SHOW_INTERVAL     3000

/**
 * @brief Struct used to store INA-219 sensor values.
 */
struct power_monitor_str {
  uint32_t count;           /**< Sampling count. */
  float actual_voltage;     /**< Sampled voltage (in V). */
  float min_voltage;        /**< Minimum sampled voltage (in V). */
  float max_voltage;        /**< Maximum sampled voltage (in V). */
  float avg_voltage;        /**< Average sampled voltage (in V). */
  float sum_voltage;        /**< Sum of all sampled voltage (in V). */
  float actual_current;     /**< Sampled current (in mA). */
  float min_current;        /**< Minimum sampled current (in mA). */
  float max_current;        /**< Maximum sampled current (in mA). */
  float avg_current;        /**< Average sampled current (in mA). */
  float sum_current;        /**< Sum of all sampled current (in mA). */
};

/* Global variables */
Adafruit_INA219 ina219_sensor = Adafruit_INA219(INA219_ADDR);   /**< INA219 object. */
MCUFRIEND_kbv tft;                                              /**< LCD object. */
power_monitor_str sensor_values;                                /**< Sensor values struct. */
uint16_t tft_id = 0;                                            /**< LCD identification. */
uint64_t last_sample = 0;                                       /**< Last sample moment (in ms). */
uint64_t last_show = 0;                                         /**< Last show moment (in ms). */

#endif
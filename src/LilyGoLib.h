/**
 * @file      LilyGoLib.h
 * @author    Lewis He (lewishe@outlook.com)
 * @license   MIT
 * @copyright Copyright (c) 2023  Shenzhen Xinyuan Electronic Technology Co., Ltd
 * @date      2023-04-28
 *
 */
#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <LittleFS.h>
#include <Wire.h>
#include <TFT_eSPI.h>
#include <lvgl.h>

#include "XPowersLib.h"
#include <TouchDrvFT6X36.hpp>
#include <SensorBMA423.hpp>
#include <SensorPCF8563.hpp>
#include <SensorDRV2605.hpp>
#include <RadioLib.h>
#include "LilyGoLib_Warning.h"

#include <driver/gpio.h>
#if ESP_IDF_VERSION < ESP_IDF_VERSION_VAL(5,0,0)
  #include <driver/temp_sensor.h>
#else
  #include <driver/temperature_sensor.h>
#endif

#ifndef USING_TWATCH_S3
  #define USING_TWATCH_S3
#endif


#if !LV_VERSION_CHECK(8,3,11)
  #warning "The current version of lvgl does not match the development version, and it is not guaranteed that the sample program can be compiled and run normally"
#endif

#if LV_SPRINTF_USE_FLOAT != 1
  #warning "Lvgl floating point support is not enabled, and some examples may not be available"
#endif

#if LV_USE_FS_POSIX != 1 || LV_FS_POSIX_LETTER != 'A'
  #warning "Lvgl fs mismatch, may not be able to use fs function"
#endif


#ifdef I2C_SDA
  #undef I2C_SDA
#endif

#ifdef I2C_SCL
  #undef I2C_SCL
#endif


#ifndef GPSSerial
  #define GPSSerial   Serial1
#endif

#include "utilities.h"


#if BOARD_TFT_MOSI  != TFT_MOSI || \
    BOARD_TFT_SCLK  != TFT_SCLK || \
    BOARD_TFT_CS    != TFT_CS   || \
    BOARD_TFT_DC    != TFT_DC   || \
    TFT_WIDTH       != BOARD_TFT_WIDTH || \
    TFT_HEIGHT      != BOARD_TFT_HEIHT
  #error  "Error! Please make sure <Setup212_LilyGo_T_Watch_S3.h> is selected in <TFT_eSPI/User_Setup_Select.h>"
#endif

#define WATCH_RADIO_ONLINE          _BV(0)
#define WATCH_TOUCH_ONLINE          _BV(1)
#define WATCH_DRV_ONLINE            _BV(2)
#define WATCH_PMU_ONLINE            _BV(3)
#define WATCH_RTC_ONLINE            _BV(4)
#define WATCH_BMA_ONLINE            _BV(5)
#define WATCH_GPS_ONLINE            _BV(6)


#define LEDC_BACKLIGHT_CHANNEL      3
#define LEDC_BACKLIGHT_BIT_WIDTH    8
#define LEDC_BACKLIGHT_FREQ         1000

//static RTC_DATA_ATTR bool log_cleared = false;

typedef enum {
    PMU_BTN_WAKEUP,
    ESP_TIMER_WAKEUP,
    SENSOR_WAKEUP,
    RTC_WAKEUP,
    TOUCH_WAKEUP
} SleepMode_t;

extern SPIClass radioBus;
#define newModule()   new Module(BOARD_RADIO_SS,BOARD_RADIO_DI01,BOARD_RADIO_RST,BOARD_RADIO_BUSY,radioBus)

/*
*   schematic pin map
*   SX12XX    CC1101
*   NRSET --> GDO0
*   BUSY  --> GDO1
* */
#define CC1101_GDO0     8
#define CC1101_GDO2     7
#define newCC1101()   new Module(BOARD_RADIO_SS,CC1101_GDO0,-1,CC1101_GDO2,radioBus)

enum PowerCtrlChannel {
    WATCH_POWER_DISPLAY_BL,
    WATCH_POWER_TOUCH_DISP,
    WATCH_POWER_RADIO,
    WATCH_POWER_DRV2605,
    WATCH_POWER_GPS,    // (The version with BOOT button and RST on the back cover)
    WATCH_POWER_GPS_DC_CHANNEL  //Earlier versions use DC3 (without BOOT button and RST)
};

class LilyGoLib :
    public TFT_eSPI,
    public TouchDrvFT6X36,
    public SensorBMA423,
    public SensorPCF8563,
    public SensorDRV2605,
#ifdef USING_TWATCH_S3
    public XPowersAXP2101
#else
    public XPowersAXP202
#endif
{
public:
    LilyGoLib();
    ~LilyGoLib();

    bool begin(Stream *stream = NULL);
    void attachPMU(void (*cb)(void));
    void attachBMA(void(*cb)(void));
    void attachRTC(void(*cb)(void));

    void setBrightness(uint8_t level);
    uint8_t getBrightness();

    void decrementBrightness(uint8_t target_level, uint32_t delay_ms = 5);
    void incrementalBrightness(uint8_t target_level, uint32_t delay_ms = 5);

    uint16_t readBMA();
    uint64_t readPMU();
    bool readRTC();

    float readAccelTemp();
    float readCoreTemp();

    void clearPMU();

    bool getTouched();

    void lowPower();
    void highPower();

    void sleepLora(bool config);
    void setSleepMode(SleepMode_t mode);

    void sleep(uint32_t second = 0) ;

    void powerIoctl(enum PowerCtrlChannel ch, bool enable);

    uint32_t getDeviceProbe();

    void disableBootDisplay();

    int writelog(const char *message);
    
private:

    void log_println(const char *message);
    bool beginPower();
    void beginCore();

    uint8_t brightness;
    Stream *stream;
    SleepMode_t sleepMode;

#if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(5,0,0)
    temperature_sensor_handle_t temp_sensor = NULL;
#endif

    uint32_t devices_probe;

    bool bootDisplay = true;
};

extern LilyGoLib watch;

#if SENSORLIB_VERSION_MINOR > 2
  #define configreFeatureInterrupt configFeatureInterrupt
#endif


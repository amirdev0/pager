/**
 * @file      pager.ino
 * @note      Arduino esp version 2.0.9 Setting , not support esp 3.x
 *            Tools ->
 *                  Board:"ESP32S3 Dev Module"
 *                  USB CDC On Boot:"Enable"
 *                  CPU Frequency: "240MHz (WiFi)"
 *                  Core Debug Level: "Verbose"
 *                  USB DFU On Boot: "Disabled"
 *                  Erase All Flash Before Sketch Upload: "Disabled"
 *                  Events Run On: "Core 1"
 *                  Flash Mode: "QI0 80MHz"
 *                  Flash Size: "16MB (128Mb)"
 *                  JTAG Adapter: "Disabled"
 *                  Arduino Runs On: "Core 1"
 *                  USB Firmware MSC On Boot: "Disabled"
 *                  Partition Scheme: "16M Flash (3MB APP/9.9MB FATFS)"
 *                  PSRAM: "OPI PSRAM"
 *                  Upload Mode: "UART0/Hardware CDC"
 *                  Upload Speed: "921600"
 *                  USB Mode: "Hardware CDC and JTAG"
 *                  Programmer: "Esptool"
 */

#include "pager.hpp"
#include "proto.hpp"

void setup()
{
    WiFi.mode(WIFI_MODE_NULL);
    btStop();
    setCpuFrequencyMhz(160);

    Serial.begin(115200);
    watch.begin(&Serial);

    settingPMU();
    settingSensor();
    settingRadio();
    
    // Initialize audio system for notifications
    initializeAudio();

    beginLvglHelper(false);
    settingButtonStyle();
    factory_ui();

    Serial.printf("Group ID: %#x\n", GROUP_ID);
    Serial.printf("Device ID: %#x\n", DEVICE_ID);


    usbPlugIn =  watch.isVbusIn();
}

void loop()
{
    SensorHandler();
    PMUHandler();

    bool screenTimeout = lv_disp_get_inactive_time(NULL) < DEFAULT_SCREEN_TIMEOUT;
    if (screenTimeout || !canScreenOff || usbPlugIn) {
        if (!screenTimeout) {
            if (usbPlugIn && (pageId != RADIO_TRANSMIT_PAGE_ID))
                createChargeUI();
            lv_disp_trig_activity(NULL);
        }
        lv_task_handler();
        delay(2);
    } else {
        lowPowerEnergyHandler2();
    }
}
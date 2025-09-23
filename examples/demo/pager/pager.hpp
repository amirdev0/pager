#pragma once

#include <LilyGoLib.h>
#include <LV_Helper.h>

#define LVGL_MESSAGE_PROGRESS_CHANGED_ID        (88)
#define RADIO_TRANSMIT_PAGE_ID                  4

#define DEFAULT_SCREEN_TIMEOUT                  15*1000
#define DEFAULT_COLOR                           (lv_color_make(252, 218, 72))

LV_IMG_DECLARE(clock_face);
LV_IMG_DECLARE(clock_hour_hand);
LV_IMG_DECLARE(clock_minute_hand);
LV_IMG_DECLARE(clock_second_hand);

LV_IMG_DECLARE(watch_if);
LV_IMG_DECLARE(watch_bg);
LV_IMG_DECLARE(watch_if_hour);
LV_IMG_DECLARE(watch_if_min);
LV_IMG_DECLARE(watch_if_sec);

LV_IMG_DECLARE(watch_if_bg2);
LV_IMG_DECLARE(watch_if_hour2);
LV_IMG_DECLARE(watch_if_min2);
LV_IMG_DECLARE(watch_if_sec2);

LV_FONT_DECLARE(font_siegra);
LV_FONT_DECLARE(font_sandbox);
LV_FONT_DECLARE(font_jetBrainsMono);
LV_FONT_DECLARE(font_firacode_60);
LV_FONT_DECLARE(font_ununtu_18);

LV_IMG_DECLARE(img_usb_plug);

LV_IMG_DECLARE(charge_done_battery);

LV_IMG_DECLARE(watch_if_5);
LV_IMG_DECLARE(watch_if_6);
LV_IMG_DECLARE(watch_if_8);

LV_IMG_DECLARE(img_temp);
LV_IMG_DECLARE(img_battery);

extern uint8_t pageId;
extern bool canScreenOff;
extern bool usbPlugIn;

static void charge_anim_cb(void *obj, int32_t v);

void radioTask(lv_timer_t *parent);

void factory_ui();

void datetimeVeiw(lv_obj_t *parent);
void analogclock3(lv_obj_t *parent);
void devicesInformation(lv_obj_t *parent);
void radioPingPong(lv_obj_t *parent);
void devicesMessages(lv_obj_t *parent);

void settingPMU();
void settingSensor();
void settingRadio();
void settingButtonStyle();
void PMUHandler();
void lowPowerEnergyHandler();
void destoryChargeUI();

static void charge_anim_cb(void *obj, int32_t v);
void createChargeUI();
void destoryChargeUI();
void PMUHandler();
void SensorHandler();
void lowPowerEnergyHandler();
void lowPowerEnergyHandler2();
void tileview_change_cb(lv_event_t *e);
void factory_ui();
void radioTask(lv_timer_t *parent);
static void draw_part_event_cb(lv_event_t *e);

void devicesMessages_add(const String& msg);
void analogclock3(lv_obj_t *parent);
static void slider_event_cb(lv_event_t *e);
static void light_sw_event_cb(lv_event_t *e);
void devicesInformation(lv_obj_t *parent);
void devicesMessages(lv_obj_t *parent);
static void radio_rxtx_cb(lv_event_t *e);
static void radio_bandwidth_cb(lv_event_t *e);
static void radio_freq_cb(lv_event_t *e);
static void radio_power_cb(lv_event_t *e);
static void radio_tx_interval_cb(lv_event_t *e);
void radioPingPong(lv_obj_t *parent);
static void progressBarSubscriberCB(lv_event_t *e);
void createProgressBar(lv_obj_t *parent);
void createButton(lv_obj_t *parent, const char *txt, lv_event_cb_t event_cb);
void settingButtonStyle();
static void lv_spinbox_event_cb(lv_event_t *e);
lv_obj_t *createAdjustButton(lv_obj_t *parent, const char *txt, lv_event_cb_t event_cb, void *user_data);
static void datetime_event_handler(lv_event_t *e);
void datetimeVeiw(lv_obj_t *parent);

/*
 ************************************
 *      HARDWARE SETTING            *
 ************************************
*/
void setSportsFlag();
void settingSensor();
void setPMUFlag();
void settingPMU();
void setRadioFlag(void);
void settingRadio();
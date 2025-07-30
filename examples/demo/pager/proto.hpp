#pragma once

#include <Arduino.h>

const uint8_t BROADCAST_HEADER = 0x01;
const uint8_t GROUP_HEADER = 0x08;
const uint8_t UNICAST_HEADER = 0x40;

const uint8_t GROUP_ID = 0x01;
const uint16_t DEVICE_ID = 0x0109;

String xorEncryptDecrypt(String input, String key);
bool checkMessage(String& msg);

#include "proto.hpp"

String xorEncryptDecrypt(String input, String key) 
{
    String output = "";
    for (int i = 0; i < input.length(); i++) {
        char encryptedChar = input.charAt(i) ^ key.charAt(i % key.length());
        output += encryptedChar;
    }
    return output;
}

bool checkMessage(String& msg)
{
    static uint8_t message_id = 0;
    if (msg[0] == message_id)
        return false;
    message_id = msg[0];
    Serial.println("Message ID: " + String(message_id));

    switch (msg[1])
    {
    case UNICAST_HEADER: {
        uint16_t device_id = (msg[2] << 8) | msg[3];
        Serial.println("Unicast device ID: " + String(device_id, HEX));
        msg.remove(0, 2);
        return device_id == DEVICE_ID;
    }
    case GROUP_HEADER:
        Serial.println("Multicast group ID: " + String(msg[2], HEX));
        msg.remove(0, 1);
        return msg[2] == GROUP_ID;
    case BROADCAST_HEADER:
        Serial.println("Broadcast entered");
        msg.remove(0, 1);
        return true;
    }
    Serial.println("Unknown message type");
    return false;
}
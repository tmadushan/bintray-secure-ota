/*
 Copyright (c) 2014-present PlatformIO <contact@platformio.org>

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
**/

#include <Arduino.h>
#include <WiFi.h>
#include "SecureOTA.h"
#include "non-blocking-utils.h"

const uint16_t OTA_CHECK_INTERVAL = 3000; // ms
uint32_t _lastOTACheck = 0;
const int ledPin =  2;// the number of the LED pin

void setup()
{
  Serial.begin(115200);
  delay(10);

  Serial.print("Device version: v.");
  Serial.println(VERSION);
  Serial.print("Connecting to " + String(WIFI_SSID));

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println(" connected!");
  _lastOTACheck = millis();

  // your setup code goes here
  pinMode(ledPin, OUTPUT);

}

void loop()
{
  if ((millis() - OTA_CHECK_INTERVAL) > _lastOTACheck) {
    _lastOTACheck = millis();
    checkFirmwareUpdates();
  }

  // your loop code goes here

  digitalWrite(ledPin, HIGH);
  non_blocking_delay(3000);

  digitalWrite(ledPin, LOW);
  non_blocking_delay(1000);
}

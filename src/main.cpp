// Copyright (c) 2021 Dave Marsh. See LICENSE.

#include <Arduino.h>
#include "esp_camera.h"
#include <WiFi.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h" // disable brownout problems
#include "esp_http_server.h"

#include "Terminal.h"
#include "setup.h"

// Replace with your network credentials

#include "/home/dave/ssid/ssid.h"
// const char *ssid = "*****";
// const char *password = "******";

const uint8_t ledPin = 33;
Terminal terminal(Serial, ledPin);

void setup()
{
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector

  // same as arduino servo-proxy
  Serial.begin(38400);
  Serial.setDebugOutput(false);

  // indicate power
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  esp_err_t err = camera_setup();
  if (err != ESP_OK)
  {
    Serial.printf("Camera init failed with error 0x%x\n%s\n",
                  err, esp_err_to_name(err));
    return;
  }

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("Connection Failed! Rebooting...");
    delay(1500);
    ESP.restart();
  }

  terminal.setup(WiFi.localIP().toString().c_str());

  err = camera_start(80);
  if (err != ESP_OK)
  {
    Serial.printf("%x: %s\n", err, esp_err_to_name(err));
  }
}

#include "Lookup.h"

void loop()
{
  if (terminal.ready())
  {
    const char *cmd = terminal.get();
    if (cmd == NULL)
    {
      return;
    }
    terminal.println(cmd);

    char variable[32] = {0};
    int val = 0;
    esp_err_t err = queryBuf(cmd, variable, sizeof(variable), &val);
    if (err != ESP_OK)
    {
      terminal.println(esp_err_to_name(err));
      return;
    }

    if (!strcmp(variable, "pan") ||
        !strcmp(variable, "tilt"))
    {
      char buffer[32];
      snprintf(buffer, sizeof(buffer),
               "%s:%d\n", variable, val);
      terminal.println(buffer);
      return;
    }

    sensor_t *sensor = esp_camera_sensor_get();
    const LookupItem *item = lookup(sensor, variable);
    if (item == NULL)
    {
      char buffer[32];
      snprintf(buffer, sizeof(buffer),
               "%s:%d NOT FOUND\n", variable, val);
      terminal.println(buffer);
      return;
    }

    err = item->action(sensor, val);
    if (err != ESP_OK)
    {
      terminal.println(esp_err_to_name(err));
      return;
    }
  }
}

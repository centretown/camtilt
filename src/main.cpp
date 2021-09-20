// Copyright (c) 2021 Dave Marsh. See LICENSE.

#ifdef ARDUINO

#include <Arduino.h>
#include "esp_camera.h"
#include <WiFi.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h" // disable brownout problems
#include "esp_http_server.h"

#include "MicroTerm.h"
#include "setup.h"
#include "Director.h"
#include "ServoActor.h"
#include "CamActor.h"

// Replace with your network credentials
#include "/home/dave/ssid/ssid.h"
// const char *ssid = "*****";
// const char *password = "******";

const uint8_t ledPin = 33;
char termBuffer[81] = {0};
MicroTerm terminal(Serial, termBuffer, sizeof(termBuffer));
Director *dir = NULL;

void setup()
{
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector

  // same as arduino servo-proxy
  Serial.begin(115200);
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

  const char *ip = WiFi.localIP().toString().c_str();
  size_t len = strlen(ip);
  if (len < 3)
  {
    ip = "unk";
  }
  const char *prefix = strrchr(ip, '.');
  if (prefix == NULL)
  {
    prefix = ip + len - 3;
  }

  terminal.setup(prefix);
  terminal.user(false);

  err = camera_start(80);
  if (err != ESP_OK)
  {
    Serial.printf("%x: %s\n", err, esp_err_to_name(err));
  }

  CamActor::initializeCamActors(esp_camera_sensor_get());
  ServoActor::initializeServoActors(&terminal);

  dir = Director::getDirector();
  dir->allocate(CamActor::actorCount + ServoActor::actorCount);
  dir->add((Actor **)ServoActor::actors, ServoActor::actorCount);
  dir->add((Actor **)CamActor::actors, CamActor::actorCount);
  dir->sort();
}

void loop()
{
  if (terminal.ready())
  {
    const char *cmd = terminal.get();
    if (cmd == NULL)
    {
      return;
    }

    char variable[32] = {0};
    esp_err_t err = queryVar(cmd, "var", variable, sizeof(variable));
    if (err != ESP_OK)
    {
      terminal.println(esp_err_to_name(err));
      return;
    }

    Actor *actor = dir->find(variable);
    if (!strcmp(actor->id, "null"))
    {
      terminal.println(esp_err_to_name(ESP_ERR_HTTPD_INVALID_REQ));
      return;
    }

    int val = 0;
    err = actor->parse(cmd);
    if (err == ActorOK)
    {
      err = actor->act(val);
    }

    if (err != ESP_OK)
    {
      terminal.println(esp_err_to_name(err));
      return;
    }
    terminal.println(cmd);
  }
}
#endif //ARDUINO

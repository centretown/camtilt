// Copyright (c) 2021 Dave Marsh. See LICENSE.
#ifdef ARDUINO

#pragma once

#include <Arduino.h>
#include <esp_http_server.h>
#include <esp_camera.h>

#include "Director.h"
#include "ControlHandler.h"
#include "StreamHandler.h"
#include "StatusHandler.h"

class CamServe
{
public:
    const sensor_t *sensor;
    uint16_t port;

    ControlHandler controlHandler;
    StreamHandler streamHandler;
    StatusHandler statusHandler;

    esp_err_t (*stream)(httpd_req_t *r);
    esp_err_t (*control)(httpd_req_t *r);
    esp_err_t (*status)(httpd_req_t *r);

public:
    CamServe() {}
    ~CamServe() {}

    esp_err_t start(uint16_t port);
    esp_err_t set_servo_id(int);
    esp_err_t set_servo_control_id(int);
    esp_err_t set_servo_index(int);

private:
    void setCrossOrigin();
};

#endif

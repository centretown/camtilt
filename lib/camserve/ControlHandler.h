// Copyright (c) 2021 Dave Marsh. See LICENSE.
#ifdef ARDUINO

#pragma once
#include <Arduino.h>
#include <esp_http_server.h>
#include "Director.h"
#include "CamHandler.h"

class ControlHandler : public CamHandler
{
private:
    Director *dir;

public:
    ControlHandler()
    {
        dir = Director::getDirector();
    }
    ~ControlHandler() {}
    esp_err_t handle(httpd_req_t *req);
};

#endif //ARDUINO

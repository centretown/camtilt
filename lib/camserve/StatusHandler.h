// Copyright (c) 2021 Dave Marsh. See LICENSE.
#ifdef ARDUINO

#pragma once
#include "CamHandler.h"

class StatusHandler : CamHandler
{
private:
public:
    StatusHandler() {}
    ~StatusHandler() {}
    esp_err_t handle(httpd_req_t *req);
};

#endif //ARDUINO

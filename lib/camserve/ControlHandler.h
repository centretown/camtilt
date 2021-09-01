#pragma once
#include <Arduino.h>
#include <esp_http_server.h>
#include "CamHandler.h"
#include "Lookup.h"

class ControlHandler : public CamHandler
{
private:
public:
    ControlHandler() {}
    ~ControlHandler() {}
    esp_err_t handle(httpd_req_t *req);
};

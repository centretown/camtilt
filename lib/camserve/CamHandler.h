// Copyright (c) 2021 Dave Marsh. See LICENSE.

#pragma once
#include "base.h"
#include "query.h"

#ifdef ARDUINO
#include "esp_camera.h"
#else
#include "MockSensor.h"
#endif


class CamHandler
{
public:
    CamHandler() {}
    ~CamHandler() {}

    static esp_err_t request(httpd_req_t *req, char *buf, size_t buf_len);
    static esp_err_t respond(httpd_req_t *req, esp_err_t res, const char* buf = NULL, size_t buflen = 0);
    virtual esp_err_t handle(httpd_req_t *req) = 0;
};

// Copyright (c) 2021 Dave Marsh. See LICENSE.

#ifdef ARDUINO

#pragma once

#include <Arduino.h>
#include <esp_http_server.h>
#include <esp_camera.h>

esp_err_t queryBuf(const char *buf, char *var, size_t varLen, int *val);
esp_err_t respond_httpd(httpd_req_t *req, esp_err_t res);
esp_err_t handle(httpd_req_t *req);

class CamHandler
{
private:
public:
    CamHandler() {}
    ~CamHandler() {}

    static esp_err_t query(httpd_req_t *req, char *buf, size_t buf_len);
    static esp_err_t respond(httpd_req_t *req, esp_err_t res);
    virtual esp_err_t handle(httpd_req_t *req) = 0;
};

#endif //ARDUINO

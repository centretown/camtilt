// Copyright (c) 2021 Dave Marsh. See LICENSE.
#ifdef ARDUINO

#pragma once

#include "CamHandler.h"

class StreamHandler : public CamHandler
{
public:
    StreamHandler(/* args */) {}
    ~StreamHandler() {}
    esp_err_t handle(httpd_req_t *req);
};

#endif //ARDUINO

// Copyright (c) 2021 Dave Marsh. See LICENSE.

#pragma once
#include "base.h"
#include "Director.h"
#include "query.h"
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


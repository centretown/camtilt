// Copyright (c) 2021 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "query.h"
#include "Actor.h"

#ifdef ARDUINO
#include "esp_camera.h"
#else
#include "MockSensor.h"
#endif

typedef struct
{
    int value;
} CamParam;

typedef esp_err_t (*CamFunc)(sensor_t *, int);

class CamActor : Actor
{
private:
    CamFunc func;
    CamParam param;

public:
    CamActor(const char *id) : Actor(id) {}

    ~CamActor() {}

    virtual err_action_t act(int action, char *out = NULL, size_t outlen = 0)
    {
        return func(sensor, param.value);
    }
    virtual err_action_t parse(const char *);
    void setFunc(CamFunc f)
    {
        func = f;
    }
    static CamActor items[];
    static void initializeCamActors(sensor_t *s);
    static CamActor **actors;
    static size_t actorCount;
    static sensor_t *sensor;
};

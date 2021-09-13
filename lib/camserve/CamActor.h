// Copyright (c) 2021 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "Actor.h"

typedef err_action_t (*CamFunc)(sensor_t *s, int i);

class CamActor : Actor
{
private:
    CamFunc func;

public:
    CamActor(const char *id) : Actor(id) {}

    ~CamActor() {}
 
    virtual err_action_t act(int action)
    {
        return func(sensor, action);
    }
    void setFunc(CamFunc f)
    {
        func = f;
    }
    static CamActor camActorItems[];
    static void initializeCamActors(sensor_t *s);
    static CamActor **camActors;
    static size_t camActorCount;
    static sensor_t *sensor;
};

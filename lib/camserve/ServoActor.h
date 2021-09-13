// Copyright (c) 2021 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "Actor.h"

typedef err_action_t (*ServoFunc)(int i);

class ServoActor : public Actor
{
private:
    ServoFunc func;

public:
    ServoActor(const char *id, ServoFunc func) : Actor(id), func(func) {}
    ~ServoActor() {}

    err_action_t act(int action)
    {
        return func(action);
    }
};

extern ServoActor *servoActors[];

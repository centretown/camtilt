// Copyright (c) 2021 Dave Marsh. See LICENSE.

#pragma once
#include "Actor.h"

class NullActor : public Actor
{
public:
    NullActor(const char *id) : Actor(id) {}

    virtual err_action_t act(int action)
    {
        return ERR_NOT_FOUND;
    }
};

extern NullActor nullActor;

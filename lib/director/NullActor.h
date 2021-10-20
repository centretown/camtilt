// Copyright (c) 2021 Dave Marsh. See LICENSE.

#pragma once
#include "Actor.h"

class NullActor : public Actor
{
public:
    NullActor(const char *id) : Actor(id) {}

    virtual err_action_t act(int action, char *out = NULL, size_t outlen = 0)
    {
        return ActorNotFound;
    }

    virtual err_action_t parse(const char *buf)
    {
        return ActorNotFound;
    }
};

extern NullActor nullActor;

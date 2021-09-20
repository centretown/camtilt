// Copyright (c) 2021 Dave Marsh. See LICENSE.

#pragma once

typedef int err_action_t;
#define ActorNotFound 9999
#define ActorOK 0

class Actor
{
public:
    const char *id;
    Actor(const char *id) : id(id) {}
    ~Actor() {}

    virtual err_action_t parse(const char *buf);
    virtual err_action_t act(int action) = 0;
};

// Copyright (c) 2021 Dave Marsh. See LICENSE.

#pragma once
// (*ActionFunc)(T *p, int v);

typedef int err_action_t;
#define ERR_NOT_FOUND 9999;

// template <class T>
class Actor
{
public:
    const char *id;
    Actor(const char *id) : id(id) {}
    ~Actor() {}

    virtual err_action_t act(int action) = 0;
};


// Copyright (c) 2021 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"

class ServoClient
{
public:
    int8_t id = 44; // last 3 ip digits
    int8_t first = 0;
    int8_t count = 2;
    ServoClient(int8_t id, int8_t first, int8_t count) : id(id), first(first), count(count) {}
    static ServoClient *clients;
    static ServoClient defaultClients[];
};

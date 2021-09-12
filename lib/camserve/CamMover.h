// Copyright (c) 2021 Dave Marsh. See LICENSE.

#include <Arduino.h>

class CamMover
{
private:
    int id;         // last 3 digits of ip
    int control_id; // last 3 digits of servo controller id
    int index;      // servo index

    IPAddress controller_ip;
public:
    CamMover(/* args */);
    ~CamMover() {}
};

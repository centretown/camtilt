// Copyright (c) 2021 Dave Marsh. See LICENSE.

#include "ServoActor.h"

err_action_t setid(int id)
{
    printf("setid %d\n", id);
    return 0;
}

err_action_t setspeed(int speed)
{
    printf("setspeed %d\n", speed);
    return 0;
}

err_action_t setangle(int angle)
{
    printf("setangle %d\n", angle);
    return 0;
}

err_action_t setmove(int angle)
{
    printf("setmove %d\n", angle);
    return 0;
}

ServoActor sa = ServoActor("id", setid);
ServoActor sb = ServoActor("speed", setspeed);
ServoActor sc = ServoActor("angle", setangle);
ServoActor sd = ServoActor("move", setmove);
ServoActor *servoActors[4] = {
    &sa,
    &sb,
    &sc,
    &sd,
};

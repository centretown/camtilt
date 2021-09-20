// Copyright (c) 2021 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "query.h"
#include "Actor.h"

#ifdef ARDUINO
#include "MicroTerm.h"
#else
#include "MockTerm.h"
#endif

#define SERVO_HOME 1
#define SERVO_MOVE 2
#define SERVO_EASE 3

typedef struct
{
    int command = 0;
    int index = 0;
    int angle = 90;
    int speed = 50;
    int type = 0;

} ServoParam;

typedef err_action_t (*ServoFunc)(ServoParam *);

class ServoActor : public Actor
{
private:
    ServoParam param;
    ServoFunc func;

public:
    ServoActor(const char *id, ServoFunc func) : Actor(id), func(func) {}
    ~ServoActor() {}

    virtual err_action_t parse(const char *);
    virtual err_action_t act(int action)
    {
        return func(&param);
    }
    static ServoActor **actors;
    static ServoActor items[];
    static size_t actorCount;
    static void initializeServoActors(MicroTerm *term);
    static MicroTerm *terminal;

private:
    static ServoParam params[];
    static err_action_t home(ServoParam *s);
    static err_action_t move(ServoParam *s);
    static err_action_t ease(ServoParam *s);
    static err_action_t send(ServoParam *s, int command);
};

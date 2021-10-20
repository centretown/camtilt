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
#define SERVO_TEST 4
#define SERVO_STOP 5

typedef struct
{
    int command = 0;
    int index = 0;
    int angle = 90;
    int speed = 50;
    int type = 0;

} ServoParam;

typedef err_action_t (*ServoFunc)(ServoParam *,char *out, size_t outlen);

class ServoActor : public Actor
{
private:
    ServoParam param;
    ServoFunc func;

public:
    ServoActor(const char *id, ServoFunc func) : Actor(id), func(func) {}
    ~ServoActor() {}

    virtual err_action_t parse(const char *);
    virtual err_action_t act(int action, char *out = NULL, size_t outlen = 0);
    static ServoActor **actors;
    static ServoActor items[];
    static size_t actorCount;
    static void initializeServoActors(MicroTerm *term);
    static MicroTerm *terminal;

private:
    static ServoParam params[];
    static err_action_t home(ServoParam *s, char *out, size_t outlen);
    static err_action_t move(ServoParam *s, char *out, size_t outlen);
    static err_action_t ease(ServoParam *s, char *out, size_t outlen);
    static err_action_t test(ServoParam *s, char *out, size_t outlen);
    static err_action_t stop(ServoParam *s, char *out, size_t outlen);
    static err_action_t send(ServoParam *s, int command, char *out, size_t outlen);
};

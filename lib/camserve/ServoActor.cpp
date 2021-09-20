// Copyright (c) 2021 Dave Marsh. See LICENSE.

#include "ServoActor.h"

err_action_t ServoActor::send(ServoParam *s, int command)
{
    char servoBuf[32] = {0};
    snprintf(servoBuf, sizeof(servoBuf), "?%d %d %d %d %d",
             command, s->index, s->angle, s->speed, s->type);
    terminal->println(servoBuf);
    return 0;
}

err_action_t ServoActor::home(ServoParam *s)
{
    return send(s, SERVO_HOME);
}

err_action_t ServoActor::ease(ServoParam *s)
{
    return send(s, SERVO_EASE);
}

err_action_t ServoActor::move(ServoParam *s)
{
    return send(s, SERVO_MOVE);
}

ServoActor **ServoActor::actors;
ServoActor ServoActor::items[] = {
    ServoActor("move", move),
    ServoActor("ease", ease),
    ServoActor("home", home),
};

size_t ServoActor::actorCount = sizeof(items) / sizeof(items[0]);

MicroTerm *ServoActor::terminal = NULL;

err_action_t ServoActor::parse(const char *qry)
{
    esp_err_t err = queryVal(qry, "index", &param.index);
    if (err != ESP_OK)
    {
        return err;
    }
    queryVal(qry, "angle", &param.angle);
    queryVal(qry, "speed", &param.speed);
    queryVal(qry, "type", &param.type);
    return ActorOK;
}

void ServoActor::initializeServoActors(MicroTerm *term)
{
    terminal = term;
    size_t size = actorCount * sizeof(ServoActor *);
    actors = (ServoActor **)malloc(size);
    for (size_t i = 0; i < actorCount; i++)
    {
        actors[i] = &items[i];
    }
}
// Copyright (c) 2021 Dave Marsh. See LICENSE.

#include "ServoActor.h"

static const char jsonFormat[] = R"rawliteral({"command":%d,"index":%d,"angle":%d,"speed":%d,"type":%d})rawliteral";

err_action_t ServoActor::send(ServoParam *s, int command, char *out, size_t outlen)
{
    char servoBuf[32] = {0};
    snprintf(servoBuf, sizeof(servoBuf), "?%d %d %d %d %d",
             command, s->index, s->angle, s->speed, s->type);

    terminal->println(servoBuf);

    if (out != NULL)
    {
        snprintf(out, outlen, jsonFormat,
                 command, s->index, s->angle, s->speed, s->type);
    }

    return 0;
}

err_action_t ServoActor::act(int action, char *out, size_t outlen)
{
    err_action_t err = func(&param, out, outlen);
    return err;
}

err_action_t ServoActor::home(ServoParam *s, char *out, size_t outlen)
{
    return send(s, SERVO_HOME, out, outlen);
}

err_action_t ServoActor::ease(ServoParam *s, char *out, size_t outlen)
{
    return send(s, SERVO_EASE, out, outlen);
}

err_action_t ServoActor::move(ServoParam *s, char *out, size_t outlen)
{
    return send(s, SERVO_MOVE, out, outlen);
}

err_action_t ServoActor::test(ServoParam *s, char *out, size_t outlen)
{
    return send(s, SERVO_TEST, out, outlen);
}

err_action_t ServoActor::stop(ServoParam *s, char *out, size_t outlen)
{
    return send(s, SERVO_STOP, out, outlen);
}

ServoActor **ServoActor::actors;
ServoActor ServoActor::items[] = {
    ServoActor("move", move),
    ServoActor("ease", ease),
    ServoActor("home", home),
    ServoActor("test", test),
    ServoActor("stop", stop),
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
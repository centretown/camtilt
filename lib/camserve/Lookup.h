// Copyright (c) 2021 Dave Marsh. See LICENSE.

#pragma once

#include <Arduino.h>
#include <esp_http_server.h>
#include <esp_camera.h>
#include <MicroTerm.h>

typedef esp_err_t (*ActionFunc)(sensor_t *s, int i);
esp_err_t queryBuf(const char *buf, char *var, size_t varLen, int *val);
void initializeLookup(sensor_t *s, MicroTerm *term);

class LookupItem
{
public:
    const char *id;
    ActionFunc action;
};

const LookupItem *find(const char *code, const LookupItem *items,
                       size_t left, size_t right);
const LookupItem *find(sensor_t *sensor, const char *code);

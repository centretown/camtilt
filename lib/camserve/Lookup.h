// Copyright (c) 2021 Dave Marsh. See LICENSE.

#pragma once

#include <Arduino.h>
#include <esp_http_server.h>
#include <esp_camera.h>

typedef esp_err_t (*ActionFunc)(sensor_t *s, int i);
esp_err_t queryBuf(const char *buf, char *var, size_t varLen, int *val);

void initLookup(sensor_t *sensor);

class LookupItem
{
public:
    const char *id;
    ActionFunc action;

private:
};

const LookupItem *find(const char *code, const LookupItem *items,
                       size_t left, size_t right);

const LookupItem *lookup(sensor_t *sensor, const char *code);
// void lookup_test(sensor_t *sensor);

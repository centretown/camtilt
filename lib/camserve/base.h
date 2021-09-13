// Copyright (c) 2021 Dave Marsh. See LICENSE.

#pragma once

#ifdef ARDUINO

#include <Arduino.h>
#include <esp_camera.h>

#else

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "sensor.h"
typedef int esp_err_t;
#define PIXFORMAT_JPEG 1

#endif

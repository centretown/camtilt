// Copyright (c) 2021 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#ifdef ARDUINO
#include "esp_http_server.h"
#else
#include "mockesp.h"
#include "MockHttpServer.h"
#endif

esp_err_t queryVar(const char *buf, const char *var, char *val, size_t valLen);
esp_err_t queryVal(const char *buf, const char *var, int *val);
esp_err_t queryBuf(const char *buf, char *var, size_t varLen, int *val);

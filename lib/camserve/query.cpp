// Copyright (c) 2021 Dave Marsh. See LICENSE.

#include "query.h"

esp_err_t queryVal(const char *buf, const char *var, int *val)
{
    char value[16];
    esp_err_t err = queryVar(buf, var, value, sizeof(value));
    if (err != ESP_OK)
    {
        return err;
    }
    *val = atoi(value);
    return ESP_OK;
}

esp_err_t queryVar(const char *buf, const char *var, char *val, size_t valLen)
{
    return httpd_query_key_value(buf, var, val, valLen);
}

esp_err_t queryBuf(const char *buf, char *var, size_t varLen, int *val)
{
    if (var == NULL || val == NULL || varLen == 0)
    {
        return ESP_ERR_HTTPD_INVALID_REQ;
    }
    esp_err_t err = queryVar(buf, "var", var, varLen);
    if (err != ESP_OK)
    {
        return err;
    }
    return queryVal(buf, "val", val);
}

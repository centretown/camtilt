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

esp_err_t queryDirector(Director *dir, const char *buf, char *out, size_t outlen)
{
    char variable[32] = {0};
    esp_err_t err = queryVar(buf, "var", variable, sizeof(variable));
    if (err != ESP_OK)
    {
        return err;
    }

    Actor *actor = dir->find(variable);
    if (!strcmp(actor->id, "null"))
    {
        return ESP_ERR_HTTPD_INVALID_REQ;
    }

    int val = 0;
    err = actor->parse(buf);
    if (err != ActorOK)
    {
        return ESP_ERR_HTTPD_INVALID_REQ;
    }

    err = actor->act(val, out, outlen);
    return err;
}

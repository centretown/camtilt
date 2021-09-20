// Copyright (c) 2021 Dave Marsh. See LICENSE.

#include "ControlHandler.h"

esp_err_t ControlHandler::handle(httpd_req_t *req)
{
    char buf[256] = {0};
    esp_err_t err = request(req, buf, sizeof(buf));
    if (err != ESP_OK)
    {
        return respond(req, err);
    }

    char variable[32] = {0};
    err = queryVar(buf, "var", variable, sizeof(variable));
    if (err != ESP_OK)
    {
        return respond(req, err);
    }

    Actor *actor = dir->find(variable);
    if (!strcmp(actor->id, "null"))
    {
        return respond(req, ESP_ERR_HTTPD_INVALID_REQ);
    }

    int val = 0;
    err = actor->parse(buf);
    if (err == ActorOK)
    {
        err = actor->act(val);
    }

    return respond(req, err);
}

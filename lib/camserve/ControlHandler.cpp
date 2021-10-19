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

    err = queryDirector(dir, buf);
    return respond(req, err);
}

#include "ControlHandler.h"

esp_err_t ControlHandler::handle(httpd_req_t *req)
{
    sensor_t *sensor = esp_camera_sensor_get();
   
    char buf[256] = {0};
    esp_err_t err = query(req, buf, sizeof(buf));
    if (err != ESP_OK)
    {
        return respond(req, err);
    }

    char variable[32] = {0};
    int val = 0;
    err = queryBuf(buf, variable, sizeof(variable), &val);
    if (err != ESP_OK)
    {
        return respond(req, err);
    }
 
    const LookupItem *lkup = lookup(sensor, variable);
    if (!lkup)
    {
        return respond(req, ESP_ERR_HTTPD_INVALID_REQ);
    }

    err = lkup->action(sensor, val);
    return respond(req, err);
}


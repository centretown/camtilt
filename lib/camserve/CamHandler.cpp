// Copyright (c) 2021 Dave Marsh. See LICENSE.
#ifdef ARDUINO

#include "CamHandler.h"

esp_err_t queryBuf(const char *buf, char *var, size_t varLen, int *val)
{
    if (var == NULL || val == NULL || varLen == 0)
    {
        return ESP_ERR_HTTPD_INVALID_REQ;
    }

    esp_err_t err = httpd_query_key_value(buf, "var", var, varLen);
    if (err != ESP_OK)
    {
        return err;
    }

    char value[32] = {0};
    err = httpd_query_key_value(buf, "val", value, sizeof(value));
    if (err != ESP_OK)
    {
        return err;
    }

    *val = atoi(value);
    return ESP_OK;
}


esp_err_t CamHandler::respond(httpd_req_t *req, esp_err_t res)
{
    if (res != ESP_OK)
    {
        return httpd_resp_send_500(req);
    }
    // httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
    // httpd_resp_set_hdr(req, "Access-Control-Max-Age", "600");
    // httpd_resp_set_hdr(req, "Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS");
    // httpd_resp_set_hdr(req, "Access-Control-Allow-Headers", "*");

    httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
    return httpd_resp_send(req, NULL, 0);
}

esp_err_t CamHandler::query(httpd_req_t *req, char *buf, size_t bufLen)
{
    size_t queryLen = httpd_req_get_url_query_len(req) + 1;
    if (bufLen < queryLen)
    {
        httpd_resp_send_404(req);
        return ESP_FAIL;
    }
    if (httpd_req_get_url_query_str(req, buf, bufLen) != ESP_OK)
    {
        httpd_resp_send_404(req);
        return ESP_FAIL;
    }
    return ESP_OK;
}

#endif //ARDUINO

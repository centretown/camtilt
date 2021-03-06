// Copyright (c) 2021 Dave Marsh. See LICENSE.

#include "CamHandler.h"

esp_err_t CamHandler::respond(httpd_req_t *req, esp_err_t err, const char *buf, size_t buflen)
{
    if (err != ESP_OK)
    {
        return httpd_resp_send_500(req);
    }
    const char *resp = NULL;
    size_t resp_length = 0;
    if (buf != NULL)
    {
        resp_length = strlen(buf);
        if (resp_length > 0)
        {
            resp = buf;
            httpd_resp_set_type(req, "application/json");
        }
    }
    httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
    return httpd_resp_send(req, resp, resp_length);
}

esp_err_t CamHandler::request(httpd_req_t *req, char *buf, size_t bufLen)
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

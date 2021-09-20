// Copyright (c) 2021 Dave Marsh. See LICENSE.

#ifndef ARDUINO

#include "MockHttpServer.h"

esp_err_t httpd_query_key_value(const char *qry,
                                const char *key,
                                char *val,
                                size_t val_size)
{
    const char *p = strstr(qry, key);
    if (p == NULL)
    {
        return ESP_ERR_NOT_FOUND;
    }

    const char *pv = strchr(p, '=');
    if (pv == NULL)
    {
        return ESP_ERR_INVALID_ARG;
    }

    pv++;

    size_t i = 0;
    for (; i < val_size; i++)
    {
        char c = pv[i];
        if (c == 0 || c == '&')
        {
            val[i] = 0;
            break;
        }
        
        val[i] = c;
    }

    if (i == val_size)
    {
        val[i - 1] = 0;
        return ESP_ERR_INVALID_ARG;
    }

    return ESP_OK;
}

esp_err_t httpd_req_get_url_query_str(httpd_req_t *r, char *buf, size_t buf_len)
{
    strncpy(buf, r->buf, buf_len);
    return ESP_OK;
}

esp_err_t httpd_resp_set_hdr(httpd_req_t *r,
                             const char *field, const char *value)
{
    return ESP_OK;
}

size_t httpd_req_get_url_query_len(httpd_req_t *r)
{
    return strlen(r->buf);
}

esp_err_t httpd_resp_send_500(httpd_req_t *r)
{
    return ESP_OK;
}

esp_err_t httpd_resp_send_404(httpd_req_t *r)
{
    return ESP_OK;
}

esp_err_t httpd_resp_send(httpd_req_t *r, const char *buf, ssize_t buf_len)
{
    return ESP_OK;
}

esp_err_t httpd_req_set_url_query_str(httpd_req_t *r, const char *buf)
{
    strncpy(r->buf, buf, sizeof(r->buf));
    return ESP_OK;
}

#endif
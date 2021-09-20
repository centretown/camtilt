// Copyright (c) 2021 Dave Marsh. See LICENSE.

#ifndef ARDUINO

#pragma once

#include "base.h"
#include "mockesp.h"

typedef struct
{
    char buf[128];
} httpd_req_t;

esp_err_t httpd_query_key_value(const char *qry, const char *key, char *val, size_t val_size);
esp_err_t httpd_resp_set_hdr(httpd_req_t *r, const char *field, const char *value);
size_t httpd_req_get_url_query_len(httpd_req_t *r);
esp_err_t httpd_req_set_url_query_str(httpd_req_t *r, const char *buf);
esp_err_t httpd_req_get_url_query_str(httpd_req_t *r, char *buf, size_t buf_len);
esp_err_t httpd_resp_send_500(httpd_req_t *r);
esp_err_t httpd_resp_send_404(httpd_req_t *r);
esp_err_t httpd_resp_send(httpd_req_t *r, const char *buf, ssize_t buf_len);

#endif


#include "CamServe.h"

static httpd_handle_t camera_httpd = NULL;
static httpd_handle_t stream_httpd = NULL;

esp_err_t CamServe::start(uint16_t port)
{
    esp_err_t err, lastErr = ESP_OK;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.server_port = port;

    httpd_uri_t status_uri = {
        .uri = "/status",
        .method = HTTP_GET,
        .handler = status,
        .user_ctx = NULL};

    httpd_uri_t cmd_uri = {
        .uri = "/action",
        .method = HTTP_GET,
        .handler = control,
        .user_ctx = NULL};

    err = httpd_start(&camera_httpd, &config);
    if (err == ESP_OK)
    {
        httpd_register_uri_handler(camera_httpd, &cmd_uri);
        httpd_register_uri_handler(camera_httpd, &status_uri);
        Serial.printf("%s started\n", cmd_uri.uri);
        Serial.printf("%s started\n", status_uri.uri);
    }
    else
    {
        lastErr = err;
        printf("failed to start command server\n  0x%x:%s\n",
               err, esp_err_to_name(err));
    }

    httpd_uri_t stream_uri = {
        .uri = "/stream",
        .method = HTTP_GET,
        .handler = stream,
        .user_ctx = NULL};

    config.server_port += 1;
    config.ctrl_port += 1;
    err = httpd_start(&stream_httpd, &config);
    if (err == ESP_OK)
    {
        httpd_register_uri_handler(stream_httpd, &stream_uri);
        Serial.printf("%s started\n", stream_uri.uri);
    }
    else
    {
        lastErr = err;
        printf("failed to start stream server\n  0x%x:%s\n",
               err, esp_err_to_name(err));
    }

    return lastErr;
}

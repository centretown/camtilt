// Copyright (c) 2021 Dave Marsh. See LICENSE.

#ifdef ARDUINO

#include "setup.h"

esp_err_t camera_setup()
{
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;

    if (psramFound())
    {
        config.frame_size = FRAMESIZE_VGA;
        config.jpeg_quality = 10;
        config.fb_count = 2;
    }
    else
    {
        config.frame_size = FRAMESIZE_SVGA;
        config.jpeg_quality = 12;
        config.fb_count = 1;
    }

    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK)
    {
        Serial.printf("Camera init failed with error 0x%x", err);
    }

    return err;
}

static CamServe serve;

static esp_err_t statusHandler(httpd_req_t *req)
{
    return serve.statusHandler.handle(req);
}

static esp_err_t streamHandler(httpd_req_t *req)
{
    return serve.streamHandler.handle(req);
}

static esp_err_t controlHandler(httpd_req_t *req)
{
    return serve.controlHandler.handle(req);
}

esp_err_t camera_start(uint16_t port)
{
    serve.status = statusHandler;
    serve.control = controlHandler;
    serve.stream = streamHandler;
    return serve.start(port);
}

#endif //ARDUINO

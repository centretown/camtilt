#pragma once
#ifndef ARDUINO
#include <stdio.h>

typedef unsigned pixformat_t;
typedef unsigned gainceiling_t;
typedef unsigned framesize_t;

class sensor_t
{
public:
    sensor_t();
    unsigned pixformat;
    int (*set_framesize)(sensor_t *sensor, framesize_t framesize);
    int (*set_contrast)(sensor_t *sensor, int level);
    int (*set_brightness)(sensor_t *sensor, int level);
    int (*set_saturation)(sensor_t *sensor, int level);
    int (*set_sharpness)(sensor_t *sensor, int level);
    int (*set_denoise)(sensor_t *sensor, int level);
    int (*set_gainceiling)(sensor_t *sensor, gainceiling_t gainceiling);
    int (*set_quality)(sensor_t *sensor, int quality);
    int (*set_colorbar)(sensor_t *sensor, int enable);
    int (*set_whitebal)(sensor_t *sensor, int enable);
    int (*set_gain_ctrl)(sensor_t *sensor, int enable);
    int (*set_exposure_ctrl)(sensor_t *sensor, int enable);
    int (*set_hmirror)(sensor_t *sensor, int enable);
    int (*set_vflip)(sensor_t *sensor, int enable);

    int (*set_aec2)(sensor_t *sensor, int enable);
    int (*set_awb_gain)(sensor_t *sensor, int enable);
    int (*set_agc_gain)(sensor_t *sensor, int gain);
    int (*set_aec_value)(sensor_t *sensor, int gain);

    int (*set_special_effect)(sensor_t *sensor, int effect);
    int (*set_wb_mode)(sensor_t *sensor, int mode);
    int (*set_ae_level)(sensor_t *sensor, int level);

    int (*set_dcw)(sensor_t *sensor, int enable);
    int (*set_bpc)(sensor_t *sensor, int enable);
    int (*set_wpc)(sensor_t *sensor, int enable);

    int (*set_raw_gma)(sensor_t *sensor, int enable);
    int (*set_lenc)(sensor_t *sensor, int enable);
};

int contrast(sensor_t *sensor, int level);
int brightness(sensor_t *sensor, int level);
int saturation(sensor_t *sensor, int level);
int sharpness(sensor_t *sensor, int level);
int denoise(sensor_t *sensor, int level);
int quality(sensor_t *sensor, int quality);
int colorbar(sensor_t *sensor, int enable);
int whitebal(sensor_t *sensor, int enable);
int gain_ctrl(sensor_t *sensor, int enable);
int exposure_ctrl(sensor_t *sensor, int enable);
int hmirror(sensor_t *sensor, int enable);
int vflip(sensor_t *sensor, int enable);

int aec2(sensor_t *sensor, int enable);
int awb_gain(sensor_t *sensor, int enable);
int agc_gain(sensor_t *sensor, int gain);
int aec_value(sensor_t *sensor, int gain);

int special_effect(sensor_t *sensor, int effect);
int wb_mode(sensor_t *sensor, int mode);
int ae_level(sensor_t *sensor, int level);

int dcw(sensor_t *sensor, int enable);
int bpc(sensor_t *sensor, int enable);
int wpc(sensor_t *sensor, int enable);

int raw_gma(sensor_t *sensor, int enable);
int lenc(sensor_t *sensor, int enable);

int gainceiling(sensor_t *sensor, int val);

int framesize(sensor_t *sensor, int val);
#endif
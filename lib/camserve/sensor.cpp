#include "sensor.h"
#ifndef ARDUINO
int prt(const char *p)
{
    printf("%s\n", p);
    return 0;
}

int framesize(sensor_t *sensor, framesize_t framesize) { return prt("set_framesize"); }
int contrast(sensor_t *sensor, int level) { return prt("set_contrast"); }
int brightness(sensor_t *sensor, int level) { return prt("set_brightness"); }
int saturation(sensor_t *sensor, int level) { return prt("set_saturation"); }
int sharpness(sensor_t *sensor, int level) { return prt("set_sharpness"); }
int denoise(sensor_t *sensor, int level) { return prt("set_denoise"); }
int gainceiling(sensor_t *sensor, gainceiling_t gainceiling) { return prt("set_gainceiling"); }
int quality(sensor_t *sensor, int quality) { return prt("set_quality"); }
int colorbar(sensor_t *sensor, int enable) { return prt("set_colorbar"); }
int whitebal(sensor_t *sensor, int enable) { return prt("set_whitebal"); }
int gain_ctrl(sensor_t *sensor, int enable) { return prt("set_gain_ctrl"); }
int exposure_ctrl(sensor_t *sensor, int enable) { return prt("set_exposure_ctrl"); }
int hmirror(sensor_t *sensor, int enable) { return prt("set_hmirror"); }
int vflip(sensor_t *sensor, int enable) { return prt("set_vflip"); }

int aec2(sensor_t *sensor, int enable) { return prt("set_aec2"); }
int awb_gain(sensor_t *sensor, int enable) { return prt("set_awb_gain"); }
int agc_gain(sensor_t *sensor, int gain) { return prt("set_agc_gain"); }
int aec_value(sensor_t *sensor, int gain) { return prt("set_aec_value"); }

int special_effect(sensor_t *sensor, int effect) { return prt("set_special_effect"); }
int wb_mode(sensor_t *sensor, int mode) { return prt("set_wb_mode"); }
int ae_level(sensor_t *sensor, int level) { return prt("set_ae_level"); }

int dcw(sensor_t *sensor, int enable) { return prt("set_dcw"); }
int bpc(sensor_t *sensor, int enable) { return prt("set_bpc"); }
int wpc(sensor_t *sensor, int enable) { return prt("set_wpc baby"); }

int raw_gma(sensor_t *sensor, int enable) { return prt("set_raw_gma"); }
int raw_lenc(sensor_t *sensor, int enable) { return prt("set_lenc"); }

#define PIXFORMAT_JPEG 1

sensor_t::sensor_t()
{
    pixformat = PIXFORMAT_JPEG;
    set_framesize = framesize;
    set_contrast = contrast;
    set_brightness = brightness;
    set_saturation = saturation;
    set_sharpness = sharpness;
    set_denoise = denoise;
    set_gainceiling = gainceiling;
    set_quality = quality;
    set_colorbar = colorbar;
    set_whitebal = whitebal;
    set_gain_ctrl = gain_ctrl;
    set_exposure_ctrl = exposure_ctrl;
    set_hmirror = hmirror;
    set_vflip = vflip;
    set_aec2 = aec2;
    set_awb_gain = awb_gain;
    set_agc_gain = agc_gain;
    set_aec_value = aec_value;
    set_special_effect = special_effect;
    set_wb_mode = wb_mode;
    set_ae_level = ae_level;
    set_dcw = dcw;
    set_bpc = bpc;
    set_wpc = wpc;
    set_raw_gma = raw_gma;
    set_lenc = raw_lenc;
}
#endif
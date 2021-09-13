// Copyright (c) 2021 Dave Marsh. See LICENSE.

#include "CamActor.h"

CamActor **CamActor::camActors = NULL;

CamActor CamActor::camActorItems[] = {
    {"ae_level"},
    {"aec"},
    {"aec2"},
    {"aec_value"},
    {"agc_gain"},
    {"awb"},
    {"awb_gain"},
    {"bpc"},
    {"brightness"},
    {"colorbar"},
    {"contrast"},
    {"dcw"},
    {"denoise"},
    {"framesize"},
    {"gainceiling"},
    {"hmirror"},
    {"lenc"},
    {"quality"},
    {"raw_gma"},
    {"saturation"},
    {"special_effect"},
    {"vflip"},
    {"wb_mode"},
    {"wpc"},
};

size_t CamActor::camActorCount = sizeof(camActorItems) / sizeof(camActorItems[0]);

sensor_t *CamActor::sensor;

esp_err_t gainceiling(sensor_t *sensor, int val)
{
    return sensor->set_gainceiling(sensor, (gainceiling_t)val);
}

esp_err_t framesize(sensor_t *sensor, int val)
{
    int res = 0;
    if (sensor->pixformat == PIXFORMAT_JPEG)
        res = sensor->set_framesize(sensor, (framesize_t)val);
    return res;
}

void CamActor::initializeCamActors(sensor_t *s)
{
    if (camActors != NULL)
    {
        return;
    }

    sensor = s;

    size_t count = sizeof(camActorItems) / sizeof(camActorItems[0]);
    size_t size = count * sizeof(CamActor *);
    camActors = (CamActor **)malloc(size);
    if (camActors == NULL)
    {
        return;
    }

    for (size_t i = 0; i < count; i++)
    {
        camActors[i] = &camActorItems[i];
        const char *variable = camActorItems[i].id;
        if (!strcmp(variable, "framesize"))
            camActorItems[i].setFunc(framesize);
        else if (!strcmp(variable, "quality"))
            camActorItems[i].setFunc(s->set_quality);
        else if (!strcmp(variable, "contrast"))
            camActorItems[i].setFunc(s->set_contrast);
        else if (!strcmp(variable, "brightness"))
            camActorItems[i].setFunc(s->set_brightness);
        else if (!strcmp(variable, "saturation"))
            camActorItems[i].setFunc(s->set_saturation);
        else if (!strcmp(variable, "gainceiling"))
            camActorItems[i].setFunc(gainceiling);
        else if (!strcmp(variable, "colorbar"))
            camActorItems[i].setFunc(s->set_colorbar);
        else if (!strcmp(variable, "awb"))
            camActorItems[i].setFunc(s->set_whitebal);
        else if (!strcmp(variable, "agc_gain"))
            camActorItems[i].setFunc(s->set_gain_ctrl);
        else if (!strcmp(variable, "aec"))
            camActorItems[i].setFunc(s->set_exposure_ctrl);
        else if (!strcmp(variable, "hmirror"))
            camActorItems[i].setFunc(s->set_hmirror);
        else if (!strcmp(variable, "vflip"))
            camActorItems[i].setFunc(s->set_vflip);
        else if (!strcmp(variable, "awb_gain"))
            camActorItems[i].setFunc(s->set_awb_gain);
        else if (!strcmp(variable, "agc_gain"))
            camActorItems[i].setFunc(s->set_agc_gain);
        else if (!strcmp(variable, "aec_value"))
            camActorItems[i].setFunc(s->set_aec_value);
        else if (!strcmp(variable, "aec2"))
            camActorItems[i].setFunc(s->set_aec2);
        else if (!strcmp(variable, "dcw"))
            camActorItems[i].setFunc(s->set_dcw);
        else if (!strcmp(variable, "denoise"))
            camActorItems[i].setFunc(s->set_denoise);
        else if (!strcmp(variable, "bpc"))
            camActorItems[i].setFunc(s->set_bpc);
        else if (!strcmp(variable, "wpc"))
            camActorItems[i].setFunc(s->set_wpc);
        else if (!strcmp(variable, "raw_gma"))
            camActorItems[i].setFunc(s->set_raw_gma);
        else if (!strcmp(variable, "lenc"))
            camActorItems[i].setFunc(s->set_lenc);
        else if (!strcmp(variable, "special_effect"))
            camActorItems[i].setFunc(s->set_special_effect);
        else if (!strcmp(variable, "wb_mode"))
            camActorItems[i].setFunc(s->set_wb_mode);
        else if (!strcmp(variable, "ae_level"))
            camActorItems[i].setFunc(s->set_ae_level);
    }
}

// CamActor ca = CamActor("framesize", sensor, framesize);
// CamActor cb = CamActor("quality", sensor, quality);
// CamActor cc = CamActor("hmirror", sensor, hmirror);
// CamActor cd = CamActor("saturation", sensor, saturation);
// CamActor ce = CamActor("brightness", sensor, brightness);
// CamActor *camActors[5] = {
//     &ca,
//     &cb,
//     &cc,
//     &cd,
//     &ce,
// };

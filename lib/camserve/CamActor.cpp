// Copyright (c) 2021 Dave Marsh. See LICENSE.

#include "CamActor.h"

CamActor **CamActor::actors = NULL;

CamActor CamActor::items[] = {
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

size_t CamActor::actorCount = sizeof(items) / sizeof(items[0]);

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

err_action_t CamActor::parse(const char *qry)
{
    esp_err_t err = queryVal(qry, "val", &param.value);
    if (err != ESP_OK)
    {
        return err;
    }
    return ActorOK;
}

void CamActor::initializeCamActors(sensor_t *s)
{
    if (actors != NULL)
    {
        return;
    }

    size_t size = actorCount * sizeof(CamActor *);
    actors = (CamActor **)malloc(size);
    if (actors == NULL)
    {
        return;
    }
    sensor = s;

    for (size_t i = 0; i < actorCount; i++)
    {
        actors[i] = &items[i];
        const char *variable = items[i].id;
        if (!strcmp(variable, "framesize"))
            items[i].setFunc(framesize);
        else if (!strcmp(variable, "quality"))
            items[i].setFunc(s->set_quality);
        else if (!strcmp(variable, "contrast"))
            items[i].setFunc(s->set_contrast);
        else if (!strcmp(variable, "brightness"))
            items[i].setFunc(s->set_brightness);
        else if (!strcmp(variable, "saturation"))
            items[i].setFunc(s->set_saturation);
        else if (!strcmp(variable, "gainceiling"))
            items[i].setFunc(gainceiling);
        else if (!strcmp(variable, "colorbar"))
            items[i].setFunc(s->set_colorbar);
        else if (!strcmp(variable, "awb"))
            items[i].setFunc(s->set_whitebal);
        else if (!strcmp(variable, "agc_gain"))
            items[i].setFunc(s->set_gain_ctrl);
        else if (!strcmp(variable, "aec"))
            items[i].setFunc(s->set_exposure_ctrl);
        else if (!strcmp(variable, "hmirror"))
            items[i].setFunc(s->set_hmirror);
        else if (!strcmp(variable, "vflip"))
            items[i].setFunc(s->set_vflip);
        else if (!strcmp(variable, "awb_gain"))
            items[i].setFunc(s->set_awb_gain);
        else if (!strcmp(variable, "agc_gain"))
            items[i].setFunc(s->set_agc_gain);
        else if (!strcmp(variable, "aec_value"))
            items[i].setFunc(s->set_aec_value);
        else if (!strcmp(variable, "aec2"))
            items[i].setFunc(s->set_aec2);
        else if (!strcmp(variable, "dcw"))
            items[i].setFunc(s->set_dcw);
        else if (!strcmp(variable, "denoise"))
            items[i].setFunc(s->set_denoise);
        else if (!strcmp(variable, "bpc"))
            items[i].setFunc(s->set_bpc);
        else if (!strcmp(variable, "wpc"))
            items[i].setFunc(s->set_wpc);
        else if (!strcmp(variable, "raw_gma"))
            items[i].setFunc(s->set_raw_gma);
        else if (!strcmp(variable, "lenc"))
            items[i].setFunc(s->set_lenc);
        else if (!strcmp(variable, "special_effect"))
            items[i].setFunc(s->set_special_effect);
        else if (!strcmp(variable, "wb_mode"))
            items[i].setFunc(s->set_wb_mode);
        else if (!strcmp(variable, "ae_level"))
            items[i].setFunc(s->set_ae_level);
    }
}

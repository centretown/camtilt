#include "Lookup.h"

// we must have order
LookupItem items[] = {
    {"ae_level", NULL},
    {"aec", NULL},
    {"aec2", NULL},
    {"aec_value", NULL},
    {"agc_gain", NULL},
    {"awb", NULL},
    {"awb_gain", NULL},
    {"bpc", NULL},
    {"brightness", NULL},
    {"colorbar", NULL},
    {"contrast", NULL},
    {"dcw", NULL},
    {"framesize", NULL},
    {"gainceiling", NULL},
    {"hmirror", NULL},
    {"lenc", NULL},
    {"pan", NULL},
    {"quality", NULL},
    {"raw_gma", NULL},
    {"saturation", NULL},
    {"special_effect", NULL},
    {"tilt", NULL},
    {"vflip", NULL},
    {"wb_mode", NULL},
    {"wpc", NULL},
};

const LookupItem *find(const char *code, const LookupItem *items,
                       size_t left, size_t right)
{
    while (left <= right)
    {
        // mid = left + (right - left) / 2;
        size_t mid = left + ((right - left) >> 1);
        int cmp = strcmp(code, items[mid].id);
        if (cmp == 0)
        {
            return &items[mid];
        }
        if (cmp > 0)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return NULL;
}

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

esp_err_t moveServo(const char *cmd, int angle)
{
    if (angle < 0)
    {
        angle = 0;
    }
    else if (angle > 180)
    {
        angle = 180;
    }
    // send cmd to servo controller
    Serial.printf("?%s:%d\n", cmd, angle);
    return 0;
}

esp_err_t pan(sensor_t *sensor, int angle)
{
    return moveServo("pan", angle);
}

esp_err_t tilt(sensor_t *sensor, int angle)
{
    return moveServo("tilt", angle);
}

sensor_t *lookup_sensor = NULL;

void initializeLookup(sensor_t *s)
{
    Serial.println("init lookup");
    lookup_sensor = s;
    for (size_t i = 0; i < sizeof(items) / sizeof(items[0]); i++)
    {
        const char *variable = items[i].id;
        if (!strcmp(variable, "framesize"))
            items[i].action = framesize;
        else if (!strcmp(variable, "quality"))
            items[i].action = lookup_sensor->set_quality;
        else if (!strcmp(variable, "contrast"))
            items[i].action = lookup_sensor->set_contrast;
        else if (!strcmp(variable, "brightness"))
            items[i].action = lookup_sensor->set_brightness;
        else if (!strcmp(variable, "saturation"))
            items[i].action = lookup_sensor->set_saturation;
        else if (!strcmp(variable, "gainceiling"))
            items[i].action = gainceiling;
        else if (!strcmp(variable, "colorbar"))
            items[i].action = lookup_sensor->set_colorbar;
        else if (!strcmp(variable, "awb"))
            items[i].action = lookup_sensor->set_whitebal;
        else if (!strcmp(variable, "agc_gain"))
            items[i].action = lookup_sensor->set_gain_ctrl;
        else if (!strcmp(variable, "aec"))
            items[i].action = lookup_sensor->set_exposure_ctrl;
        else if (!strcmp(variable, "hmirror"))
            items[i].action = lookup_sensor->set_hmirror;
        else if (!strcmp(variable, "vflip"))
            items[i].action = lookup_sensor->set_vflip;
        else if (!strcmp(variable, "awb_gain"))
            items[i].action = lookup_sensor->set_awb_gain;
        else if (!strcmp(variable, "agc_gain"))
            items[i].action = lookup_sensor->set_agc_gain;
        else if (!strcmp(variable, "aec_value"))
            items[i].action = lookup_sensor->set_aec_value;
        else if (!strcmp(variable, "aec2"))
            items[i].action = lookup_sensor->set_aec2;
        else if (!strcmp(variable, "dcw"))
            items[i].action = lookup_sensor->set_dcw;
        else if (!strcmp(variable, "bpc"))
            items[i].action = lookup_sensor->set_bpc;
        else if (!strcmp(variable, "wpc"))
            items[i].action = lookup_sensor->set_wpc;
        else if (!strcmp(variable, "raw_gma"))
            items[i].action = lookup_sensor->set_raw_gma;
        else if (!strcmp(variable, "lenc"))
            items[i].action = lookup_sensor->set_lenc;
        else if (!strcmp(variable, "special_effect"))
            items[i].action = lookup_sensor->set_special_effect;
        else if (!strcmp(variable, "wb_mode"))
            items[i].action = lookup_sensor->set_wb_mode;
        else if (!strcmp(variable, "ae_level"))
            items[i].action = lookup_sensor->set_ae_level;
        else if (!strcmp(variable, "pan"))
            items[i].action = pan;
        else if (!strcmp(variable, "tilt"))
            items[i].action = tilt;
    }
}

const LookupItem *lookup(sensor_t *s, const char *code)
{
    if (lookup_sensor != s)
    {
        initializeLookup(s);
    }
    return find(code, items, 0,
                sizeof(items) / sizeof(items[0]) - 1);
}

esp_err_t queryBuf(const char *buf, char *var, size_t varLen, int *val)
{
    if (var == NULL || val == NULL || varLen == 0)
        return ESP_ERR_HTTPD_INVALID_REQ;

    char value[32] = {0};
    esp_err_t err = httpd_query_key_value(buf, "var", var, varLen);
    if (err != ESP_OK)
    {
        return err;
    }
    err = httpd_query_key_value(buf, "val", value, sizeof(value));
    if (err != ESP_OK)
    {
        return err;
    }

    *val = atoi(value);
    return ESP_OK;
}
// Copyright (c) 2021 Dave Marsh. See LICENSE.

#include "StatusHandler.h"

static const char statusFormat[] = R"rawliteral({"framesize":%u,
"quality":%u,
"brightness":%d,
"contrast":%d,
"saturation":%d,
"sharpness":%d,
"special_effect":%u,
"wb_mode":%u,
"awb":%u,
"awb_gain":%u,
"aec":%u,
"aec2":%u,
"ae_level":%d,
"aec_value":%u,
"agc":%u,
"agc_gain":%u,
"gainceiling":%u,
"bpc":%u,
"wpc":%u,
"raw_gma":%u,
"lenc":%u,
"vflip":%u,
"hmirror":%u,
"dcw":%u,
"colorbar":%u})rawliteral";

esp_err_t StatusHandler::handle(httpd_req_t *req)
{
    sensor_t *sensor = esp_camera_sensor_get();
    char json_response[sizeof(statusFormat) * 2];
    snprintf(json_response, sizeof(json_response), statusFormat,
             sensor->status.framesize,
             sensor->status.quality,
             sensor->status.brightness,
             sensor->status.contrast,
             sensor->status.saturation,
             sensor->status.sharpness,
             sensor->status.special_effect,
             sensor->status.wb_mode,
             sensor->status.awb,
             sensor->status.awb_gain,
             sensor->status.aec,
             sensor->status.aec2,
             sensor->status.ae_level,
             sensor->status.aec_value,
             sensor->status.agc,
             sensor->status.agc_gain,
             sensor->status.gainceiling,
             sensor->status.bpc,
             sensor->status.wpc,
             sensor->status.raw_gma,
             sensor->status.lenc,
             sensor->status.vflip,
             sensor->status.hmirror,
             sensor->status.dcw,
             sensor->status.colorbar);

    esp_err_t err = httpd_resp_set_type(req, "application/json");
    if (err)
        return respond(req, err);
    err = httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
    if (err)
        return respond(req, err);
    return httpd_resp_send(req, json_response, strlen(json_response));
}

// Copyright (c) 2021 Dave Marsh. See LICENSE.


#ifndef ARDUINO

#pragma once
#include "base.h"

typedef int32_t esp_err_t;

/* Definitions for error constants. */
#define ESP_OK 0    /*!< esp_err_t value indicating success (no error) */
#define ESP_FAIL -1 /*!< Generic esp_err_t code indicating failure */

#define ESP_ERR_NO_MEM 0x101           /*!< Out of memory */
#define ESP_ERR_INVALID_ARG 0x102      /*!< Invalid argument */
#define ESP_ERR_INVALID_STATE 0x103    /*!< Invalid state */
#define ESP_ERR_INVALID_SIZE 0x104     /*!< Invalid size */
#define ESP_ERR_NOT_FOUND 0x105        /*!< Requested resource not found */
#define ESP_ERR_NOT_SUPPORTED 0x106    /*!< Operation or feature not supported */
#define ESP_ERR_TIMEOUT 0x107          /*!< Operation timed out */
#define ESP_ERR_INVALID_RESPONSE 0x108 /*!< Received response was invalid */
#define ESP_ERR_INVALID_CRC 0x109      /*!< CRC or checksum was invalid */
#define ESP_ERR_INVALID_VERSION 0x10A  /*!< Version was invalid */
#define ESP_ERR_INVALID_MAC 0x10B      /*!< MAC address was invalid */

#define ESP_ERR_WIFI_BASE 0x3000 /*!< Starting number of WiFi error codes */
#define ESP_ERR_MESH_BASE 0x4000 /*!< Starting number of MESH error codes */

#define ESP_ERR_HTTPD_BASE (0x8000)                           /*!< Starting number of HTTPD error codes */
#define ESP_ERR_HTTPD_HANDLERS_FULL (ESP_ERR_HTTPD_BASE + 1)  /*!< All slots for registering URI handlers have been consumed */
#define ESP_ERR_HTTPD_HANDLER_EXISTS (ESP_ERR_HTTPD_BASE + 2) /*!< URI handler with same method and target URI already registered */
#define ESP_ERR_HTTPD_INVALID_REQ (ESP_ERR_HTTPD_BASE + 3)    /*!< Invalid request pointer */
#define ESP_ERR_HTTPD_RESULT_TRUNC (ESP_ERR_HTTPD_BASE + 4)   /*!< Result string truncated */
#define ESP_ERR_HTTPD_RESP_HDR (ESP_ERR_HTTPD_BASE + 5)       /*!< Response header field larger than supported */
#define ESP_ERR_HTTPD_RESP_SEND (ESP_ERR_HTTPD_BASE + 6)      /*!< Error occured while sending response packet */
#define ESP_ERR_HTTPD_ALLOC_MEM (ESP_ERR_HTTPD_BASE + 7)      /*!< Failed to dynamically allocate memory for resource */
#define ESP_ERR_HTTPD_TASK (ESP_ERR_HTTPD_BASE + 8)           /*!< Failed to launch server task/thread */

#endif

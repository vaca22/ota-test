//
// Created by vaca on 7/26/22.
//

#ifndef ESP32_OTA_SDCARD_H
#define ESP32_OTA_SDCARD_H
#include <stdio.h>
#include <string.h>
#include "esp_system.h"
#include "esp_log.h"
#include "esp_console.h"
#include "esp_vfs_dev.h"
#include "driver/uart.h"

#include "argtable3/argtable3.h"
#include "esp_vfs_fat.h"
#include "nvs.h"
#include "nvs_flash.h"

#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include <esp_ota_ops.h>
#include "sdcard_services.h"

typedef enum {
    OTA_FILE_NOT_FOUND,
    OTA_FAIL,
    OTA_IN_PROGRESS,
    OTA_SUCCESS
} ota_info_status;


/**
 *
 * 这是ota回调函数
   infoStatus   ota状态信息。
   progress当前写入flash的字节数
   file_len 文件总字节数
 *
 */

typedef void(*ota_info)(ota_info_status infoStatus, int progress,int  file_len);


esp_err_t ota_from_sdcard(char *path,ota_info callback);
esp_err_t ota_spiffs_from_sdcard(char *path,ota_info callback);
#endif //ESP32_NAT_ROUTER_OTA_SDCARD_H

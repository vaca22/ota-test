/**
 * @file sdcard_services.h
 * sdcard_services file
 */
#ifndef __SDCARD_H__
#define __SDCARD_H__

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "driver/sdmmc_host.h"
#include "esp_log.h"
#include "esp_vfs.h"
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*********************
 *      DEFINES
 *********************/
#define MOUNT_POINT "/sdcard"

#define BOOK_RECORD "/sdcard/books_record.json"  // 教材学习情况记录文件(json)
#define CATALOGUE_JSON "/sdcard/catalogue.json"  // 课程资源目录文件(json)
#define PERSON_DATA_JSON "/sdcard/person.json"

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
esp_err_t sd_card_init();
esp_err_t sd_card_test();

int sd_card_get_file_size(char *filepath);
bool sd_card_read_file(char *filepath, char *buf, size_t len);
bool sd_card_write_file(char *filepath, char *buf, size_t len);
/**********************
 *      MACROS
 **********************/

bool sd_is_mounted;

esp_err_t spiffs_mount_storage(const char* base_path);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*__file_H__*/

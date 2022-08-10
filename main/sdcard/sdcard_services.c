/**
 * @file sdcard_services.c
 * sdcard_services file
 */

/*********************
 *      INCLUDES
 *********************/
#include "sdcard_services.h"

/*********************
 *      DEFINES
 *********************/
#define TAG "file"
/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
static sdmmc_card_t *sdcard;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
esp_err_t sd_card_init() {
    esp_err_t ret;

    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = false,
        .max_files              = 5,
        .allocation_unit_size   = 16 * 1024};

    const char mount_point[] = MOUNT_POINT;

    sdmmc_host_t host               = SDMMC_HOST_DEFAULT();
    sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();

    slot_config.width = 1;
    slot_config.flags |= SDMMC_SLOT_FLAG_INTERNAL_PULLUP;

    ESP_LOGI(TAG, "SDIO初始化成功");

    ret = esp_vfs_fat_sdmmc_mount(mount_point, &host, &slot_config,
                                  &mount_config, &sdcard);

    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "初始化失败");
        sd_is_mounted = false;
        return ESP_FAIL;
    }
    ESP_LOGI(TAG, "文件系统挂在成功");
    sd_is_mounted = true;
    sdmmc_card_print_info(stdout, sdcard);

    return ESP_OK;
}

int sd_card_get_file_size(char *filepath) {
    if (NULL == filepath) return 0;
    struct stat filestat = {0};
    if (0 == stat(filepath, &filestat))
        return filestat.st_size;
    else
        return -1;
}

bool sd_card_read_file(char *filepath, char *buf, size_t len) {
    FILE *fp = fopen(filepath, "r");
    if (fp == NULL) {
        ESP_LOGI(__FILE__, "sd_card_read_file error fp == NULL");
        fclose(fp);
        return false;
    }

    size_t count = fread(buf, 1, len, fp);

    fclose(fp);

    return (count == len) ? true : false;
}

bool sd_card_write_file(char *filepath, char *buf, size_t len) {
    FILE *fp = fopen(filepath, "wb");
    if (fp == NULL) {
        ESP_LOGI(__FILE__, "sd_card_read_file error fp == NULL");
        fclose(fp);
        return false;
    }

    size_t count = fwrite(buf, 1, len, fp);
    fclose(fp);

    return (count == len) ? true : false;
}

#include "cJSON.h"
#include "cJSON_Utils.h"

// 要开启 CONFIG_FATFS_LONG_FILENAMES :)
esp_err_t sd_card_test() {
#warning "正式工程不得调用此函数 ==> sd_card_test"

    DIR *dir;
    struct dirent *ptr;
    dir = opendir(MOUNT_POINT "/");
    printf("sd card file list:\n");
    while ((ptr = readdir(dir)) != NULL) {
        printf("\t"MOUNT_POINT"/%s\n", ptr->d_name);
    }
    closedir(dir);

    return ESP_OK;
}
/**********************
 *   STATIC FUNCTIONS
 **********************/

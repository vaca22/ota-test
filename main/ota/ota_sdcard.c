//
// Created by vaca on 7/26/22.
//

#include "ota_sdcard.h"



#define  ota_mtu 4096
static char buf_ota[ota_mtu];
const char *TAG = "ota";

esp_err_t ota_from_sdcard(char *path,ota_info callback) {

    esp_err_t err;
    int file_len=0;

    struct stat entry_stat;

    if (stat(path, &entry_stat) == -1) {
        ESP_LOGE(TAG, "Failed to stat");
        if(callback){
            callback(OTA_FILE_NOT_FOUND,0,0);
        }
        return ESP_FAIL;
    }

    ESP_LOGI("file", "  %ld", entry_stat.st_size);
    file_len=entry_stat.st_size;



    esp_ota_handle_t update_handle = 0;
    const esp_partition_t *update_partition = NULL;
    update_partition = esp_ota_get_next_update_partition(NULL);
    if(update_partition==NULL){
        if(callback){
            callback(OTA_FAIL,0,0);
        }
        return ESP_FAIL;
    }


    err =esp_ota_begin(update_partition, OTA_WITH_SEQUENTIAL_WRITES, &update_handle);

    if (err != ESP_OK) {
        esp_ota_abort(update_handle);
        if(callback){
            callback(OTA_FAIL,0,0);
        }
        return ESP_FAIL;
    }

    FILE *f = fopen(path, "rb");
    if (f == NULL) {
        if(callback){
            callback(OTA_FILE_NOT_FOUND,0,0);
        }
        return ESP_FAIL;
    }

    int file_have_write=0;
    int read_len=0;
    while(file_have_write!=file_len){
        read_len=fread(buf_ota,1,ota_mtu,f);
        err = esp_ota_write( update_handle, (const void *)buf_ota, read_len);
        if (err != ESP_OK) {
            esp_ota_abort(update_handle);
            if(callback){
                callback(OTA_FAIL,0,0);
            }
            return ESP_FAIL;
        }
        file_have_write+=read_len;
        if(callback){
            callback(OTA_IN_PROGRESS,file_have_write,file_len);
        }
    }
    ESP_LOGI("file", "read end  %ld", entry_stat.st_size);

    err =esp_ota_end(update_handle);
    if (err != ESP_OK) {
        if(callback){
            callback(OTA_FILE_NOT_FOUND,0,0);
        }
        return ESP_FAIL;
    }

    err=esp_ota_set_boot_partition(update_partition);
    if (err != ESP_OK) {
        if(callback){
            callback(OTA_FILE_NOT_FOUND,0,0);
        }
        return ESP_FAIL;
    }
    fclose(f);
    if(callback){
        callback(OTA_SUCCESS,file_len,file_len);
    }

    return ESP_OK;
}

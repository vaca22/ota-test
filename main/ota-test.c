#include <stdio.h>
#include "sdcard_services.h"
#include "ota_sdcard.h"


void ota_callback(ota_info_status infoStatus, int progress,int  file_len){
    ESP_LOGE("good","%d  %d  %d",infoStatus,progress,file_len);
}

void app_main(void)
{
    sd_card_init();
  //  ota_from_sdcard("/sdcard/ota/toycloud_m01_esp32.bin",ota_callback) ;
    spiffs_mount_storage("/data");


    FILE *f = fopen("/data/gaga.txt", "rb");
    if (f == NULL) {
        ESP_LOGE("TAG", "Failed to open file for reading");
        return;
    }
    ESP_LOGE("TAG", "Failed to opsdfdsen file for reading");
    // Read a line from file
    char line[64];
    fread(line, 1,4, f);
    line[4]=0;
    ESP_LOGE("TAG","%s",line);
    fclose(f);
}

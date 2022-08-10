#include <stdio.h>
#include "sdcard_services.h"
#include "ota_sdcard.h"


void ota_callback(ota_info_status infoStatus, int progress,int  file_len){
    ESP_LOGE("good","%d  %d  %d",infoStatus,progress,file_len);
}

void app_main(void)
{
    sd_card_init();
    ota_from_sdcard("/sdcard/ota/toycloud_m01_esp32.bin",ota_callback) ;
}

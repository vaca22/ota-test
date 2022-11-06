file(GLOB_RECURSE SOURCES ./*.c)
idf_component_register(SRCS  ${SOURCES}
                    INCLUDE_DIRS "."
                    "ota"
                    "sdcard"

        )

spiffs_create_partition_image(storage ../spiffs FLASH_IN_PROJECT)
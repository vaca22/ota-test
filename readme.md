esptool.py  --chip esp32 merge_bin -fs 4MB 0x1000 build/bootloader/bootloader.bin \
0x8000 build/partition_table/partition-table.bin \
0xf000 build/ota_data_initial.bin \
0x20000 build/ota-test.bin \
0xa0000 build/a.bin -o xxxxx-merge.bin
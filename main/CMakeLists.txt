idf_component_register(SRCS "main.cpp" "Application.cpp" "u8g2_esp32_hal.c" "config.cpp"
                    INCLUDE_DIRS ".")
#spiffs_create_partition_image(storage ../spiffs FLASH_IN_PROJECT)
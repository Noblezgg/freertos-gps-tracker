idf_component_register(SRCS "main.c"
                            "gps-uart/nmea.c"
                    PRIV_REQUIRES spi_flash
                    REQUIRES esp_event esp_driver_uart
                    INCLUDE_DIRS "."
                    )

target_compile_definitions(${COMPONENT_LIB} PUBLIC "-DLOG_LOCAL_LEVEL=ESP_LOG_VERBOSE")
/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
*/

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "gps-uart/nmea.h"
#include "esp_system.h"
#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include "esp_log.h"
 
// static const char *RX_TASK_TAG = "RX_TASK";
 
static const char *TAG = "gps_demo";

#define TIME_ZONE (+8)   //Beijing Time
#define YEAR_BASE (2000) //date in GPS starts from 2000

/**
* @brief GPS Event Handler
*
* @param event_handler_arg handler specific arguments
* @param event_base event base, here is fixed to ESP_NMEA_EVENT
* @param event_id event id
* @param event_data event specific arguments
*/
static void gps_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    gps_t *gps = NULL;
    switch (event_id) {
    case GPS_UPDATE:
        gps = (gps_t *)event_data;
        /* print information parsed from GPS statements */
        ESP_LOGI(TAG, "%d/%d/%d %d:%d:%d => \r\n"
                "\t\t\t\t\t\tlatitude   = %.05f°N\r\n"
                "\t\t\t\t\t\tlongitude = %.05f°E\r\n"
                "\t\t\t\t\t\taltitude   = %.02fm\r\n"
                "\t\t\t\t\t\tspeed      = %fm/s",
                gps->date.year + YEAR_BASE, gps->date.month, gps->date.day,
                gps->tim.hour + TIME_ZONE, gps->tim.minute, gps->tim.second,
                gps->latitude, gps->longitude, gps->altitude, gps->speed);
        break;
    case GPS_UNKNOWN:
        /* print unknown statements */
        ESP_LOGW(TAG, "Unknown statement:%s", (char *)event_data);
        break;
    default:
        break;
    }
}

void app_main(void)
{
    /* NMEA parser configuration */
    nmea_parser_config_t config = NMEA_PARSER_CONFIG_DEFAULT();
    /* init NMEA parser library */
    nmea_parser_handle_t nmea_hdl = nmea_parser_init(&config);
    /* register event handler for NMEA parser library */
    nmea_parser_add_handler(nmea_hdl, gps_event_handler, NULL);
 
    vTaskDelay(10000 / portTICK_PERIOD_MS);
 
    /* unregister event handler */
    nmea_parser_remove_handler(nmea_hdl, gps_event_handler);
    /* deinit NMEA parser library */
    nmea_parser_deinit(nmea_hdl);
}
/* Test task
@author Nidchenko Illia
@brief Test task for developing firmware for ESP32 module.
Write a program to send HTTP requests to the remote server.
Program should connect to the WiFi, get commands from the console (UART),
send requests to the server, and output responses to the console.
 */
#include <string.h>
#include "esp_log.h"
#include "nvs_flash.h"
#include "protocol_examples_common.h"
#include "esp_http_client.h"
#include "esp_console.h"
#include "cli.h"
#include "http_request.h"

static const char *TAG = "Canyon Task";

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    ESP_ERROR_CHECK(example_connect());
    register_http_prompt(do_http_request);
    cli_process();
}

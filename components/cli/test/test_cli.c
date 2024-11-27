#include "unity.h"
#include "cli.h"

TEST_CASE("register_http_prompt", "[CLI]")
{
    int (*http_request_ptr)(int, char**) = NULL;

    esp_console_cmd_register_ExpectAnyArgsAndReturn(ESP_OK);
    register_http_prompt(http_request_ptr);
}
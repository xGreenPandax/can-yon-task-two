#include <string.h>
#include "esp_log.h"
#include "esp_console.h"

void cli_process()
{
    esp_console_repl_t *repl = NULL;
    esp_console_repl_config_t repl_config = ESP_CONSOLE_REPL_CONFIG_DEFAULT();
    repl_config.prompt = CONFIG_IDF_TARGET ">";
    repl_config.max_cmdline_length = 200;
#if defined(CONFIG_ESP_CONSOLE_UART_DEFAULT) || defined(CONFIG_ESP_CONSOLE_UART_CUSTOM)
    esp_console_dev_uart_config_t hw_config = ESP_CONSOLE_DEV_UART_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_console_new_repl_uart(&hw_config, &repl_config, &repl));
#elif defined(CONFIG_ESP_CONSOLE_USB_SERIAL_JTAG)
    esp_console_dev_usb_serial_jtag_config_t hw_config = ESP_CONSOLE_DEV_USB_SERIAL_JTAG_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_console_new_repl_usb_serial_jtag(&hw_config, &repl_config, &repl));
#else
#error "Setup channel for console output in menuconfig"
#endif
    ESP_ERROR_CHECK(esp_console_start_repl(repl));
}

void register_http_prompt(int (*http_request_ptr)(int argc, char **argv))
{
    const esp_console_cmd_t http_prompt_cmd = {
        .command = "http",
        .help = "http <REQ> <URL> <BODY>\n\
                REQ - GET or POST request.\n\
                URL - remote server address. For example http://httpbin.org\n\
                BODY - request body in case of POST.\n",
        .hint = NULL,
        .func = http_request_ptr,
    };

    ESP_ERROR_CHECK(esp_console_cmd_register(&http_prompt_cmd));
}
#include <string.h>
#include "esp_log.h"
#include "esp_http_client.h"
#include "http_request.h"

int do_http_request(int argc, char **argv)
{
    const char *req = argv[1];
    if ((argc < 3) || (!(argc == 3 && !strcmp(req, "GET")) && !(argc == 4 && !strcmp(req, "POST"))))
    {
        ESP_LOGE("http", "Incorrect number of arguments");
        return -1;
    }
    const char *url = argv[2];
    const char *body = argv[3];

    ESP_LOGI("http", "Received arguments:");
    ESP_LOGI("http", "  req: %s", req);
    ESP_LOGI("http", "  url: %s", url);
    ESP_LOGI("http", "  body: %s", body == NULL ? "" : body);

    esp_http_client_config_t config = {
        .url = url,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);

    if (!strcmp(req, "GET"))
    {
        // GET
        esp_http_client_set_url(client, url);
        esp_err_t err = esp_http_client_perform(client);
        if (err == ESP_OK)
        {
            ESP_LOGI("http", "HTTP GET Status = %d, content_length = %" PRId64,
                     esp_http_client_get_status_code(client),
                     esp_http_client_get_content_length(client));
        }
        else
        {
            ESP_LOGE("http", "HTTP GET request failed: %s", esp_err_to_name(err));
        }
    }
    else
    {
        // POST
        esp_http_client_set_url(client, url);
        esp_http_client_set_method(client, HTTP_METHOD_POST);
        esp_http_client_set_header(client, "Content-Type", "text/plain");
        esp_http_client_set_post_field(client, body, strlen(body));
        esp_err_t err = esp_http_client_perform(client);
        if (err == ESP_OK)
        {
            ESP_LOGI("http", "HTTP POST Status = %d, content_length = %" PRId64,
                     esp_http_client_get_status_code(client),
                     esp_http_client_get_content_length(client));
        }
        else
        {
            ESP_LOGE("http", "HTTP POST request failed: %s", esp_err_to_name(err));
        }
    }
    return 0;
}
#pragma once

void cli_process();
void register_http_prompt(int (*http_request_ptr)(int argc, char **argv));
#pragma once

#include <string>
#define PORT 8080

namespace http {

int create();
void handleConnection(int client_fd);
void validate(std::string request);
void process(std::string file);

void test();
} // namespace http

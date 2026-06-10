#pragma once

#include <string>
#include "./response/GetRes.hpp"
#define PORT 8080

namespace http {

int create();
void handleConnection(int client_fd);
void validate(std::string request);
GetRes processGET(std::string raw);
void process(std::string file);

void test();
} // namespace http

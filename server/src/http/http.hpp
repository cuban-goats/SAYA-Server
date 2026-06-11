#pragma once

#include "./response/GetRes.hpp"
#include <string>
#define PORT 8080

namespace http {

int create();
void handleConnection(int client_fd);
void validate(std::string request);
GetRes processGET(std::string raw);
void process(std::string file, int client_fd);

void test();

std::optional<std::string> serve(std::string);
} // namespace http

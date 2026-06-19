#pragma once

#include "./response/GetRes.hpp"
#include "request/GetRq.hpp"
#include <filesystem>
#include <string>

namespace fs = std::filesystem;
#define PORT 8080

namespace http {

int create();
void handleConnection(int client_fd);
void validate(std::string request);
GetRes processGET(std::string raw);
void process(std::string file, int client_fd);

void handleWebSocket();

void test(GetRq rq);

std::optional<std::string> serve(std::string);
std::string getContentType(fs::path file);
std::string getContentLenght(std::string content);
} // namespace http

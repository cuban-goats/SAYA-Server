#include "./http.hpp"
#include "./request//GetRq.hpp"
#include "./response/GetRes.hpp"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <netinet/in.h>
#include <optional>
#include <ostream>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

namespace fs = std::filesystem;

namespace http {

int create() {
  int server_fd, client_fd;
  struct sockaddr_in address;
  int opt = 1;
  int addrlen = sizeof(address);

  // Create socket
  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd == 0) {
    perror("socket creation failed");
    exit(EXIT_FAILURE);
  }

  // Attach socket to the port
  setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  // Bind
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  // Listen
  if (listen(server_fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
    std::cerr << "could not listen to fd: " << server_fd << std::endl;
  }
  std::cout << "connected to fd: " << server_fd << std::endl;

  // Accept a connection
  while (1) {
    std::cout << "Waiting for requests ..." << std::endl;
    sleep(1);

    client_fd =
        accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    if (client_fd < 0) {
      perror("accept");
      exit(EXIT_FAILURE);
      std::cerr << " could not accept fd: " << server_fd << std::endl;
    }
    std::cout << " accepted connection from fd: " << server_fd << std::endl;

    handleConnection(client_fd);

    // Close socket
    close(client_fd);
  }
  close(server_fd);
  return 0;
};

// read request from client and process it
void handleConnection(int client_fd) {
  char buffer[1024] = {0};
  std::string raw;
  while (true) {
    int r = read(client_fd, buffer, sizeof(buffer));
    if (r <= 0) {
      break;
    }
    raw.append(buffer, r);
    if (raw.find("\r\n\r\n") != std::string::npos) {
      break;
    }
  }
  process(raw, client_fd);
  std::cout << "Client Request for:\n" << buffer << std::endl;
}

void process(std::string rawReq, int client_fd) {
  size_t methodEnd = rawReq.find(" ", 0);
  std::string method = rawReq.substr(0, methodEnd);
  if (method == "GET") {
    GetRes res = processGET(rawReq);
    std::string resStr = res.tcpStringify();
    send(client_fd, resStr.c_str(), resStr.size(), 0);
  } else if (method == "POST") {
    std::cout << "POST not implemented yet ..." << std::endl;
  } else {
    std::cout << "Invalid request method ..." << std::endl;
  }
}

GetRes processGET(std::string raw) {
  std::cout << "processing GET request ..." << std::endl;
  GetRq get(raw);
  auto content = serve(get.rq.path);

  std::map<std::string, std::string> headers;
  // Host header
  headers.insert({"Content-Type", getContentType(get.rq.path)});
  headers.insert({"Content-Length", getContentLenght(*content)});

  if (content) {
    // search for 404 not found html page in website and then return that for
    // body if it exists
    return GetRes(
        {
            "HTTP/1.1",
            200,
            "OK",
        },
        headers, {*content});
  } else {
    return GetRes(
        {
            "HTTP/1.1",
            404,
            "Not Found",
        },
        headers, {"Error: File not found"});
  }
}

std::optional<std::string> serve(std::string filePath) {
  fs::path p = "../public/"; // relative to ./server/build/
  if (!filePath.empty() && filePath[0] == '/') {
    filePath = filePath.substr(1);
  }
  p.append(filePath);
  p = fs::absolute(p);
  std::cout << p << std::endl;
  if (!fs::exists(p)) {
    std::cerr << "file not found !" << std::endl;
    return std::nullopt;
  }
  std::ifstream file(p);
  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string content = buffer.str();
  return content;
};

std::string getContentType(fs::path file) {
  std::string ext = file.extension().c_str();
  if (ext == ".html")
    return "text/html";
  if (ext == ".css")
    return "text/css";
  if (ext == ".js")
    return "application/javascript";
  if (ext == ".json")
    return "application/json";
  if (ext == ".png")
    return "image/png";
  if (ext == ".jpg" || ext == ".jpeg")
    return "image/jpeg";
  return "appication/octet-stream";
}

std::string getContentLenght(std::string content) {
  return std::to_string(content.size());
}

//------------------------------------------------------------
void test() {
  std::string testBuffer =
      "GET /products HTTP/1.1\r\nHost: host\r\nUser-Agent: "
      "userAgent\r\nAccept: accept\r\nAccept-Language: "
      "acceptLang\r\nAccept-Encoding: "
      "acceptEnc\r\nConnection: connected\r\n\r\n";
  GetRq get(testBuffer);

  auto content = serve(get.rq.path);

  std::map<std::string, std::string> testHeaders = {
      {"Host", "host"}, {"User-Agent", "userAgent"}};

  if (!content) {
    GetRes res(
        {
            "HTTP/1.1",
            404,
            "Not Found",
        },
        testHeaders, {"body"});
    res.tcpStringify();
  } else {
    GetRes res(
        {
            "HTTP/1.1",
            200,
            "OK",
        },
        testHeaders, {content->c_str()});
    res.tcpStringify();
  }
}

} // namespace http

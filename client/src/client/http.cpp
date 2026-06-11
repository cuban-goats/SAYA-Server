#include "./http.hpp"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

namespace http {

int create(const char *url) {
  int sock = 0;
  struct sockaddr_in serv_addr;

  // Create socket
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    std::cerr << "Socket creation error" << std::endl;
    return -1;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);

  // Convert IPv4 and IPv6 addresses from text to binary
  if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
    std::cerr << "Invalid address/ Address not supported" << std::endl;
    return -1;
  }

  // Connect to server
  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    std::cerr << "Connection Failed" << std::endl;
    return -1;
  }

  // Send data
  const char *testBuffer =
      "GET website/index.html HTTP/1.1\r\nHost: host\r\nUser-Agent: "
      "userAgent\r\nAccept: accept\r\nAccept-Language: "
      "acceptLang\r\nAccept-Encoding: "
      "acceptEnc\r\nConnection: connected\r\n\r\n";

  send(sock, testBuffer, strlen(testBuffer), 0);
  std::cout << "Message sent" << std::endl;

  // Receive data
  char buffer[1024] = {0};

  read(sock, buffer, 1024);
  std::cout << "Server responded with: " << buffer << std::endl;

  // Close socket
  close(sock);
  return 0;
};

} // namespace http

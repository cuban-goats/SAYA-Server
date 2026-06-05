#include "./http.hpp"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>

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
  read(client_fd, buffer, 1024);
  std::cout << "Client Request for: " << buffer << std::endl;
  send(client_fd, "Hello from server", strlen("Hello from server"), 0);
}

void process(std::string rawReq) {
  // size_t str = std::find_first_of(rawReq, "GET");
}

void validate(std::string request) {
  // read until first " " then decide type of request
  //
  // corresponding processing funciton validate correct request format with
  // header, ...
}

} // namespace http

#include "client/http.hpp"
#include "client/Request.hpp"
#include <iostream>

int main() {
  const char *request = "GET /index.html";

  rq::Request req(request);
  int e = http::create(request);
  std::cout << "client: " << e << std::endl;

  return 0;
}

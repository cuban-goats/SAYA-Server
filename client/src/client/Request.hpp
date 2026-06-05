#pragma once
#include <string>

namespace rq {
class Request {
public:
  static std::string url;
  Request(std::string);
  void get();
  void validate();

private:
};

} // namespace rq

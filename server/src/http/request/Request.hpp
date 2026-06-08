#pragma once

// Request interface
#include "HttpTypes.hpp"
#include <map>

class Request {
public:
  virtual RequestLine getRequestLine() = 0;
  virtual std::map<std::string, std::string> getHeaders() = 0;

  virtual void setRequestLine(std::string method, std::string path,
                              std::string version) = 0;
  virtual void setHeaders(std::map<std::string, std::string> headers) = 0;

  virtual void byteEncode() = 0;
};

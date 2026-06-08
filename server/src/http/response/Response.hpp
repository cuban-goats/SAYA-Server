#pragma once

// Request interface
#include "HttpTypes.hpp"
#include <map>

class Response {
public:
  virtual StatusLine getStatusLine() = 0;
  virtual std::map<std::string, std::string> getHeader() = 0;
  virtual Body getBody() = 0;

  virtual void setStatusLine(StatusLine) = 0;
  virtual void setHeader(std::map<std::string, std::string>) = 0;
  virtual void setBody(Body) = 0;

  virtual void byteEncode() = 0; // encodes all information including headers, etc.

  virtual ~Response() = default;
};

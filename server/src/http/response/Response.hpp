#pragma once

// Request interface
#include "../HttpTypes.hpp"
#include <map>

class Response {
public:
  virtual StatusLine getStatusLine() = 0;
  virtual std::map<std::string, std::string> getHeader() = 0;
  virtual Body getBody() = 0;
  virtual size_t getBodyBytes() = 0;

  virtual void setStatusLine(StatusLine) = 0;
  virtual void setHeader(std::map<std::string, std::string>) = 0;
  virtual void setBody(Body) = 0;

  virtual ~Response() = default;
};

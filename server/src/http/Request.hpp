#pragma once

// Request interface
#include <optional>
#include <string>
#include "HttpTypes.hpp"

class Get;
class Post;

class Request {
public:
  virtual RequestLine getRequestLine() = 0;
  virtual Header getHeader() = 0;

  virtual void setRequestLine(RequestLine) = 0;
  virtual void setHeader(Header) = 0;

  virtual void byteEncode() = 0; // encodes all information including headers, etc.
};


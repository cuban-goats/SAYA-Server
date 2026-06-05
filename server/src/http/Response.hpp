#pragma once

// Request interface
#include <string>

struct RequestLine {
  std::string method;
  std::string path;
  float version;
};

struct Header {
  std::string date;
  std::string host;
  std::string contentType;
  std::string contentLength;
  std::string cacheControl;
  std::string connection;
  // separator line to body
};

struct Body {
  std::string body; // where the html goes
};

class Response {
public:
  virtual RequestLine getRequestLine();
  virtual Header getHeader();
  virtual std::optional<std::string> getBody();

  virtual void setRequestLine(RequestLine);
  virtual void setHeader(Header);
  virtual std::optional<void> setBody(std::string);

  virtual void parse(char buffer[1024]);
  virtual void byteEncode(); // encodes all information including headers, etc.
};

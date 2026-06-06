#pragma once

#include <string>

struct RequestLine {
  std::string method;
  std::string path;
  std::string version;
};

struct Header {
  std::string host;
  std::string userAgent;
  std::string accept;
  std::string acceptLanguage;
  std::string acceptEncoding;
  std::string connection;

  // separator line to body
};

struct Body {
  std::string body;
};

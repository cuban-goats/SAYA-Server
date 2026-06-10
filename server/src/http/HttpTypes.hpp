#pragma once

#include <string>

struct RequestLine {
  std::string method;
  std::string path;
  std::string version;
};

struct StatusLine {
  std::string version;
  uint16_t statusCode;
  std::string reasonPhrase;
};

struct Body {
  std::string body;
};

//-----------------------------------

struct Header {
  std::string host;
  std::string userAgent;
  std::string accept;
  std::string acceptLanguage;
  std::string acceptEncoding;
  std::string connection;
};

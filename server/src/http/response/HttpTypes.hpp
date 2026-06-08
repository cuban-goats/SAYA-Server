#pragma once

#include <string>

struct StatusLine {
  std::string method;
  std::string path;
  std::string version;
};

struct Body {
  std::string body;
};

#pragma once

#include "Request.hpp"

class Post : public Request {
public:
  RequestLine rq;
  Header h;
  Body b;

  RequestLine getRequestLine() override;
  std::map<std::string, std::string> getHeaders() override;
  std::string getBody();

  void setRequestLine(RequestLine);
  void setHeader(Header);
  void setBody(Header);

  Post parse(char buffer[1024]);
  void byteEncode() override;
};

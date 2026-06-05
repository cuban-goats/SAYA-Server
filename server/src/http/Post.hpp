#pragma once

#include "Request.hpp"

class Post : public Request {
public:
  RequestLine rq;
  Header h;
  Body b;

  RequestLine getRequestLine() override;
  Header getHeader() override;
  std::string getBody();

  void getRequestLine(RequestLine);
  void getHeader(Header);
  void setBody(Header);

  Post parse(char buffer[1024]);
  void byteEncode() override;
};

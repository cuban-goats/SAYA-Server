#pragma once

#include "Request.hpp"

class Post : public Request {
public:
  RequestLine rq;
  std::string h;
  Body b;

  RequestLine getRequestLine() override;
  std::map<std::string, std::string> getHeaders() override;
  std::string getBody();

  void setRequestLine(RequestLine);
  void setHeader(std::map<std::string, std::string>);
  void setBody(std::string);

  Post parse(char buffer[1024]);
  void byteEncode() override;
};

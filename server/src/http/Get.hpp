#pragma once

#include "Request.hpp"

class Get : public Request {
public:
  RequestLine rq;
  Header h;

  RequestLine getRequestLine() override;
  Header getHeader() override;

  void setRequestLine(RequestLine) override;
  void setHeader(Header) override;

  Get parse(char buffer[1024]);
  void byteEncode() override;
};

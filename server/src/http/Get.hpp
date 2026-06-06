#pragma once

#include "Request.hpp"
#include <map>

class Get : public Request {
public:
  RequestLine rq;
  Header h;

  RequestLine getRequestLine() override;
  Header getHeader() override;

  void setRequestLine(RequestLine) override;
  void setHeader(Header) override;

  Get parse(char buffer[1024]);
  Get parseByLine(std::string buffer);
  void byteEncode() override;

  void skipNewLine(int i, char buffer[1024]);
  void printI(RequestLine rqLine, Header header);
  std::string getNextLine(const std::string &raw, size_t &pos);
};

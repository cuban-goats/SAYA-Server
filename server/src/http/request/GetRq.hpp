#pragma once

#include "Request.hpp"
#include <map>

class GetRq : public Request {
public:
  RequestLine rq;
  std::map<std::string, std::string> headers;

  RequestLine getRequestLine() override;
  std::map<std::string, std::string> getHeaders() override;

  void setRequestLine(std::string method, std::string path,
                      std::string version) override;

  void setHeaders(std::map<std::string, std::string> headers) override;

  GetRq parseByLine(std::string buffer);
  void byteEncode() override;

  void printI(GetRq request);
  std::string getNextLine(const std::string &raw, size_t &pos);

  //----------------------------------------
  GetRq parse(char buffer[1024]);
  void skipNewLine(int i, char buffer[1024]);
};

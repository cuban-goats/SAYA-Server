#pragma once

#include "HttpTypes.hpp"
#include "Response.hpp"

class GetRes : public Response {
public:
  GetRes(StatusLine sl, std::map<std::string, std::string> headers, Body body);

  StatusLine sL;
  std::map<std::string, std::string> headers;
  Body body;

  StatusLine getStatusLine() override;
  std::map<std::string, std::string> getHeader() override;
  Body getBody() override;

  void setStatusLine(StatusLine) override;
  void setHeader(std::map<std::string, std::string>) override;
  void setBody(Body) override;

  void addHeader(std::string, std::string);

  void byteEncode() override; // encodes all information including headers, etc.
};

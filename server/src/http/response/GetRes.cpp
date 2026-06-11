#include "GetRes.hpp"
#include <cstdio>
#include <iostream>
#include <ostream>
#include <string>

GetRes::GetRes(StatusLine sl, std::map<std::string, std::string> headers,
               Body body)
    : sL(sl), headers(headers), body(body) {};

StatusLine GetRes::getStatusLine() { return sL; };

std::map<std::string, std::string> GetRes::getHeader() { return headers; };

Body GetRes::getBody() { return body; };
size_t GetRes::getBodyBytes() { return body.body.size(); };

void GetRes::setStatusLine(StatusLine status) { sL = status; };
void GetRes::setHeader(std::map<std::string, std::string> h) { headers = h; };
void GetRes::setBody(Body b) { body = b; };

void GetRes::addHeader(std::string name, std::string value) {
  headers.insert({name, value});
};

std::string GetRes::tcpStringify() {
  StatusLine sLine = getStatusLine();
  std::string respString = sLine.version + " " +
                           std::to_string(sLine.statusCode) + " " +
                           sLine.reasonPhrase + "\r\n";
  for (auto const &[key, value] : headers) {
    respString.append(key + ": " + value + "\r\n");
  }
  respString.append("\r\n");
  respString.append(getBody().body);
  printf("\n");
  std::cout << respString << std::endl;
  return respString;
};


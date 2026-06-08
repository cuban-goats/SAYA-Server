#include "GetRes.hpp"

GetRes::GetRes(StatusLine sl, std::map<std::string, std::string> headers,
               Body body)
    : sL(sl), headers(headers), body(body) {};

StatusLine GetRes::getStatusLine() { return sL; };

std::map<std::string, std::string> GetRes::getHeader() { return headers; };

Body GetRes::getBody() { return body; };

void GetRes::setStatusLine(StatusLine){};
void GetRes::setHeader(std::map<std::string, std::string>){};
void GetRes::setBody(Body){};

void GetRes::addHeader(std::string name, std::string value) {
  headers.insert({name, value});
};

void GetRes::byteEncode() {};

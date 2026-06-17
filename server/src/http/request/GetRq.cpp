#include "GetRq.hpp"
#include "../HttpTypes.hpp"
#include <cctype>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

// find out what to set the size to
// check if char is " ", if not save the char (allocate mem for it)
// if " " save the part into the request object

GetRq::GetRq(std::string raw) { parseByLine(raw); };

RequestLine GetRq::getRequestLine() { return rq; };
std::map<std::string, std::string> GetRq::getHeaders() { return headers; };

void GetRq::setRequestLine(std::string method, std::string path,
                           std::string version) {
  rq.method = method;
  rq.path = path;
  rq.version = version;
};

void GetRq::setHeaders(std::map<std::string, std::string> headersI) {
  headers = headersI;
};

void GetRq::parseByLine(std::string buffer) {
  size_t pos = 0;

  size_t endOMethod = buffer.find(" ", pos) + 1;
  size_t endOPath = buffer.find(" ", endOMethod) + 1;
  size_t endOVersion = buffer.find("\r\n", endOPath);
  setRequestLine(buffer.substr(pos, endOMethod - 1),
                 buffer.substr(endOMethod, endOPath - endOMethod - 1),
                 buffer.substr(endOPath, endOVersion - endOPath));

  pos = endOVersion + 2;

  std::string line;

  while ((line = getNextLine(buffer, pos)) != "") {
    size_t i;
    std::string name;
    std::string value;

    i = line.find(": ");
    if (i == std::string::npos)
      continue;
    name = line.substr(0, i);
    value = line.substr(i + 2);
    headers.insert({name, value});
  }
  printI(*this);
};

std::string GetRq::getNextLine(const std::string &raw, size_t &pos) {
  size_t end = raw.find("\r\n", pos);
  if (end == std::string::npos)
    return "";
  std::string line = raw.substr(pos, end - pos);
  pos = end + 2;
  return line;
}

void GetRq::printI(GetRq request) {
  printf("Method: %s, Path: %s, Version: %s\n", request.rq.method.c_str(),
         request.rq.path.c_str(), request.rq.version.c_str());

  for (auto header : request.headers) {
    std::cout << "(name) " << header.first << ": " << "(value) "
              << header.second << std::endl;
  }
}

void GetRq::byteEncode() {};

void GetRq::handleWebSocket() {
  // get required headers
  //   if (m.contains("a")) {
  //     int val = m["a"];
  // }
};

//---------------------------------------------------------

GetRq GetRq::parse(char buffer[1024]) {
  RequestLine rq;
  Header h;
  printf("\n%s\n\n", buffer);

  char *line = buffer;
  char *next;

  size_t size = 0;
  int t = 0; // tokenCounter

  char *token = (char *)std::malloc(size);

  int bufLen = 1024;

  for (int i = 0; i < bufLen; i++) {
    if (buffer[i] == '\r') {
      skipNewLine(i, buffer);
    } else if (!isspace(buffer[i])) {
      void *temp = std::realloc(token, ++size);
      if (temp == NULL) {
        free(token);
        break;
      } else {
        token = (char *)temp;
        token[size - 1] = buffer[i];
      }
    } else if (isspace(buffer[i])) {
      void *temp = std::realloc(token, size + 1);
      if (temp == NULL) {
        free(token);
        break;
      }
      token = (char *)temp;
      token[size] = '\0';

      std::string *rqL[] = {&rq.method, &rq.path, &rq.version};
      std::string *header[] = {&h.host,           &h.userAgent,
                               &h.accept,         &h.acceptLanguage,
                               &h.acceptEncoding, &h.connection};
      if (t < 3) {
        *rqL[t] = token;
      } else if (t < 8) {
        *header[t - 3] = token;
      }

      t++;
      size = 0;
      free(token);
      token = (char *)std::malloc(size);
    } else {
      free(token);
    }
  }
  printI(*this);
  if (token != NULL) {
    free(token);
  }

  return *this;
};

void GetRq::skipNewLine(int i, char buffer[1024]) {
  buffer[i] = ' ';
  if (i + 1 <= strlen(buffer) && buffer[i + 1] == '\n') {
    buffer[i] = ' ';
  }
};

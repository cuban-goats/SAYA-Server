#include "Get.hpp"
#include "Request.hpp"
#include <cctype>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// find out what to set the size to
// check if char is " ", if not save the char (allocate mem for it)
// if " " save the part into the request object
//
RequestLine Get::getRequestLine() { return rq; };
Header Get::getHeader() { return h; };

void Get::setRequestLine(RequestLine){};
void Get::setHeader(Header){};

Get Get::parse(char buffer[1024]) {
  RequestLine rqLine;
  Header header;

  printf("\n%s\n\n", buffer);

  char *line = buffer;
  char *next;

  int s = 0;
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

      std::string *rqL[] = {&rqLine.method, &rqLine.path, &rqLine.version};
      std::string *h[] = {&header.host, &header.userAgent, &header.accept,
                          &header.acceptLanguage, &header.connection};
      if (t < 3) {
        *rqL[t] = token;
      } else if (t < 8) {
        *h[t - 3] = token;
      }

      t++;
      size = 0;
      free(token);
      token = (char *)std::malloc(size);
    } else {
      free(token);
    }
  }
  printf("Method: %s, Path: %s, Version: %s\n", rqLine.method.c_str(),
         rqLine.path.c_str(), rqLine.version.c_str());
  printf(
      "Host: %s, UserAgent: %s, Accept: %s, AcceptLanguage: %s, Connection: %s",
      header.host.c_str(), header.userAgent.c_str(), header.accept.c_str(),
      header.acceptLanguage.c_str(), header.connection.c_str());
  if (token != NULL) {
    free(token);
  }

  Get result;
  result.rq = rq;
  result.h = h;
  return result;
};

void Get::skipNewLine(int i, char buffer[1024]) {
  buffer[i] = ' ';
  if (i + 1 <= strlen(buffer) && buffer[i + 1] == '\n') {
    buffer[i] = ' ';
  }
};

void Get::byteEncode() {};

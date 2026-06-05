#include "Get.hpp"
#include "Request.hpp"
#include <algorithm>
#include <cctype>
#include <cstddef>
#include <cstdio>
#include <cstdlib>

// find out what to set the size to
// check if char is " ", if not save the char (allocate mem for it)
// if " " save the part into the request object
//
RequestLine Get::getRequestLine() { return rq; };
Header Get::getHeader() { return h; };

void Get::setRequestLine(RequestLine){};
void Get::setHeader(Header){};

Get Get::parse(char buffer[1024]) {
  RequestLine rq;
  Header h;

  printf("\n%s\n\n", buffer);

  int s = 0;
  size_t size = 0;
  int t = 0; // tokenCounter

  char *token = (char *)std::malloc(size);

  for (int i = 0; i < 23; i++) {
    if (!isspace(buffer[i])) {
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

      std::string *fields[] = {&rq.method, &rq.path, &rq.version};
      if (t < 3) {
        *fields[t] = token;
      }
      t++;
      size = 0;
      free(token);
      token = (char *)std::malloc(size);
    } else {
      free(token);
    }
  }
  printf("Method: %s, Path: %s, Version: %s\n", rq.method.c_str(),
         rq.path.c_str(), rq.version.c_str());
  if (token != NULL) {
    free(token);
  }

  Get result;
  result.rq = rq;
  result.h = h;
  return result;
};

void Get::byteEncode() {};

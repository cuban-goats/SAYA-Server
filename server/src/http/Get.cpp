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
      if (temp == nullptr) {
        free(token);
        break;
      } else {
        token = (char *)temp;
        token[size - 1] = buffer[i];
      }
    } else if (isspace(buffer[i])) {
      void *temp = std::realloc(token, size + 1);
      token = (char *)temp;
      token[size] = '\0';
      if (t == 0) {
        rq.method = token;
        printf("Method: %s ", rq.method.c_str());
      } else if (t == 1) {
        rq.path = token;
        printf("Path: %s ", rq.path.c_str());
      } else if (t == 2) {
        rq.version = token;
        printf("Version: %s\n", rq.version.c_str());
      }
      t++;
      size = 0;

      printf("\n");
      free(token);
      token = (char *)std::malloc(size);
    } else {
      free(token);
    }
  }
  if (token != NULL) {
    free(token);
  }

  Get result;
  result.rq = rq;
  result.h = h;
  return result;
};

void Get::byteEncode() {};

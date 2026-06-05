#include "Get.hpp"
#include <cctype>
#include <cstddef>
#include <cstdlib>

Request Get::parse(char buffer[1024]) { // find out what to set the size to
  int s = 0;
  char* token =(char*)std::malloc(0);
  void *ptr = malloc(1);
  size_t size;

  for (int i = 0; i < 1024; i++) {
    if (!isspace(buffer[i])) {
      token = (char*)std::realloc(token, ++size);
    } else {
      free(ptr);
      s++;
    }

    // check if char is " ", if not save the char (allocate mem for it)
    // if " " save the part into the request object
  }
};

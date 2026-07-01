#include "Crypt.hpp"
#include <iostream>
#include <openssl/evp.h>
#include <string>

namespace crypt {

std::string base64Decode(std::string in) {
  unsigned char* decoded;
  std::vector<unsigned char> buffer(in.begin(), in.end());
  unsigned char* bufferPtr = buffer.data();
  int len = 0;
  int resLen = EVP_DecodeBlock(decoded, bufferPtr, len);
  if (resLen == -1) {
    std::cerr << "failed to decode block" << std::endl;
    return NULL;
  }
  return "";
};

} // namespace crypt

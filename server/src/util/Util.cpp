#include "Util.hpp"
#include <string>

namespace util {

bool contains(std::string s, std::string part) {
  std::string lowerCase = s;
  for (char &c : lowerCase) {
    c = std::tolower(static_cast<unsigned char>(c));
  }
  if (lowerCase.find(part) != std::string::npos) {
    return true;
  }
  return false;
};

} // namespace util

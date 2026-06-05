#include "Request.hpp"

class Post : public Request {
public:
  RequestLine getRequestLine() override;
  Header getHeader() override;
  std::optional<std::string> getBody() override;

  void getRequestLine(RequestLine);
  void getHeader(Header);
  std::optional<void> setBody(Header);

  void parse() override;
};

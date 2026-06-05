#include "Request.hpp"

class Get : public Request {
public:
  RequestLine getRequestLine() override;
  Header getHeader() override;

  void getRequestLine(RequestLine);
  void getHeader(Header);

  void parse() override;
};

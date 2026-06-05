#include "Request.hpp"

class Get : public Request {
public:
  RequestLine rq;
  Header h;

  RequestLine getRequestLine() override;
  Header getHeader() override;

  void getRequestLine(RequestLine);
  void getHeader(Header);

  Request parse(char buffer[1024]) override;
};

#include "./Request.hpp"
namespace rq {

Request::Request(std::string url_) {
  this->url = url_;
}

void Request::get() {};
void Request::validate() {};

std::string Request::url;

} // namespace rq

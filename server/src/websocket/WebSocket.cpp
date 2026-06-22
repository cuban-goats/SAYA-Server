#include "WebSocket.hpp"
#include "../http/request/GetRq.hpp"
#include "../util/Util.hpp"

using namespace ws;

WebSocket::WebSocket(int c_fd) : client_fd(c_fd) {};

bool isWebsocketUpgrade(GetRq rq) {
  std::map<std::string, std::string> h = rq.getHeaders();
  std::string wsUpgrade;
  std::string wsConnection;
  if ((h.find("Upgrade") != h.end()) && (h.find("Upgrade") != h.end())) {
    wsUpgrade = h.at("Upgrade");
    wsConnection = h.at("Connection");

    if (util::contains(wsUpgrade, "websocket") && util::contains(wsConnection, "Upgrade")) {
      return true;
    }
  }
  return false;
};

void WebSocket::validate() {}; // validate key and version
void WebSocket::handshake() {};
void WebSocket::readFrame() {};
void WebSocket::sendFrame() {};
void WebSocket::close() {};


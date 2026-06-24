#include "WebSocket.hpp"
#include "../http/request/GetRq.hpp"
#include "../util/Util.hpp"
#include <iostream>
#include <map>
#include <string>

namespace ws {

void handleWebSocket(GetRq rq, int client_fd) {
  if (isWebsocketUpgrade(rq)) {
    std::map<std::string, std::string> h = rq.getHeaders();
    if (isValid(h)) {
      std::string key = h.at("Sec-WebSocket-Key");
      std::string version = h.at("Sec-WebSocket-Version");
      // TODO: handshake somewhere here
      WebSocket w(client_fd, h);
    } else {
      // respond with GetRes 101
    }
  }
};

bool isWebsocketUpgrade(GetRq rq) {
  std::map<std::string, std::string> h = rq.getHeaders();
  std::string wsUpgrade;
  std::string wsConnection;
  if ((h.find("Upgrade") != h.end()) && (h.find("Upgrade") != h.end())) {
    wsUpgrade = h.at("Upgrade");
    wsConnection = h.at("Connection");

    if (util::contains(wsUpgrade, "websocket") &&
        util::contains(wsConnection, "Upgrade")) {
      return true;
    }
  }
  return false;
};

bool isValid(std::map<std::string, std::string> h) {
  if (h.find("Host") == h.end()) {
    std::cout << "no host specified" << std::endl;
    return false;
  }
  if (h.find("Origin") == h.end()) {
    std::cout << "no origin specified" << std::endl;
    return false;
  }
  if (h.find("Sec-WebSocket-Key") == h.end()) {
    std::cout << "no Sec-WebSocket-Key specified" << std::endl;
    // TODO: validate size by decoding to 16 Bytes
    return false;
  }
  if (h.find("Sec-WebSocket-Version") == h.end()) {
    std::cout << "no Sec-WebSocket- specified" << std::endl;
    return false;
  }
  return true;
};

WebSocket::WebSocket(int c_fd, std::map<std::string, std::string> wsH)
    : client_fd(c_fd), wsHeaders(wsH) {};

void WebSocket::setWebSocketHeaders(std::map<std::string, std::string> h) {
  wsHeaders = h;
};

void WebSocket::handshake() {};
void WebSocket::readFrame() {};
void WebSocket::sendFrame() {};
void WebSocket::close() {};

} // namespace ws

#include "WebSocket.hpp"

using namespace websocket;

WebSocket::WebSocket(int c_fd) : client_fd(c_fd) {};

void WebSocket::handshake() {};
void WebSocket::readFrame() {};
void WebSocket::sendFrame() {};
void WebSocket::close() {};

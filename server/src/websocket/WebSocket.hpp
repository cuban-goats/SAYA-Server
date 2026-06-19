namespace websocket {

class WebSocket {
public:
  // store client_fd
  void handshake();
  void readFrame();
  void sendFrame();
  void close();
};
} // namespace websocket

namespace websocket {

class WebSocket {
public:
  int client_fd;
  WebSocket(int client_fd);

  // store client_fd
  void handshake();
  void readFrame();
  void sendFrame();
  void close();
};
} // namespace websocket

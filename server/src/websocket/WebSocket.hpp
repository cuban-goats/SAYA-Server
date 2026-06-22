#include "../http/request/GetRq.hpp"

namespace ws {
bool isWebsocketUpgrade(GetRq rq);

class WebSocket {
public:
  int client_fd;
  WebSocket(int client_fd);

  // store client_fd
  void validate();
  void handshake();
  void readFrame();
  void sendFrame();
  void close();
};
} // namespace ws

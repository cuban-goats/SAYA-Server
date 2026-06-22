#include "../http/request/GetRq.hpp"

namespace ws {
bool isWebsocketUpgrade(GetRq rq);
void handleWebSocket(GetRq rq, int client_fd);

class WebSocket {
public:
  int client_fd;
  WebSocket(int client_fd);

  void validate();
  void handshake();
  void readFrame();
  void sendFrame();
  void close();
};
} // namespace ws

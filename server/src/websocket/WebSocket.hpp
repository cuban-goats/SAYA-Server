#include "../http/request/GetRq.hpp"
#include <map>

namespace ws {
bool isWebsocketUpgrade(GetRq rq);
void handleWebSocket(GetRq rq, int client_fd);
bool isValid(std::map<std::string, std::string> wsHeaders);

class WebSocket {
public:
  int client_fd;
  // requiredWebSocketHeaders wsHeaders;
  std::map<std::string, std::string> wsHeaders;
  WebSocket(int client_fd, std::map<std::string, std::string> wsH);

  void setWebSocketHeaders(std::map<std::string, std::string> h);
  void handshake();
  void readFrame();
  void sendFrame();
  void close();
};
} // namespace ws

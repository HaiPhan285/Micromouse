
#pragma once

#include <string>

namespace MM {
class Simulation {
public:
  explicit Simulation();

  bool isConnected() const {
    return connected_;
  }

  void logMsg(const std::string& text);
  bool wallFront();
  bool wallRight();
  bool wallLeft();
  void moveForward();
  void turnRight();
  void turnLeft();
  void turnAround();
  void setText(int x, int y, const std::string& text);
  void setColor(int x, int y, char color);

private:
  std::string readResponse(const char* command);

  bool connected_{true};
};
} // namespace MM

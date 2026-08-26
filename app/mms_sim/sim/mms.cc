#include "mms.h"
#include <iostream>

namespace MM {

Simulation::Simulation() {}

void Simulation::logMsg(const std::string& text) {
  std::cerr << text << std::endl;
}

void Simulation::setText(int x, int y, const std::string& text) {
  std::cout << "setText " << x << " " << y << " " << text << std::endl;
}

void Simulation::setColor(int x, int y, char color) {
  std::cout << "setColor " << x << " " << y << " " << color << std::endl;
}

bool Simulation::wallFront() {
  return readResponse("wallFront") == "true";
}

bool Simulation::wallRight() {
  return readResponse("wallRight") == "true";
}

bool Simulation::wallLeft() {
  return readResponse("wallLeft") == "true";
}

void Simulation::moveForward() {
  readResponse("moveForward");
}

void Simulation::turnRight() {
  readResponse("turnRight");
}

void Simulation::turnLeft() {
  readResponse("turnLeft");
}

void Simulation::turnAround() {
  turnRight();
  turnRight();
}

std::string Simulation::readResponse(const char* command) {
  std::cout << command << std::endl;

  std::string response;
  if (!(std::cin >> response)) {
    connected_ = false;
  }
  return response;
}

} // namespace MM

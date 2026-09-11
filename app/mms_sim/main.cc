#include "floodfill.h"
#include "sim/mms.h"

using namespace MM;
int main() {
  Simulation sim;
  sim.logMsg("Running Floodfill in MMS Simulator...");

  MM::Floodfill mouseAlgo;

  while (sim.isConnected()) {
    bool f_wall = sim.wallFront();
    if (!sim.isConnected()) {
      break;
    }

    bool r_wall = sim.wallRight();
    if (!sim.isConnected()) {
      break;
    }

    bool l_wall = sim.wallLeft();
    if (!sim.isConnected()) {
      break;
    }

    mouseAlgo.set_sensor_data(f_wall, r_wall, l_wall);

    mouseAlgo.update();

    for (int x = 0; x < 16; ++x) {
      for (int y = 0; y < 16; ++y) {
        unsigned char dist = mouseAlgo.get_distance(x, y);
        sim.setText(x, y, std::to_string(dist));

        if ((x == 7 || x == 8) && (y == 7 || y == 8)) {
          sim.setColor(x, y, 'G');
        }
      }
    }

    char move = mouseAlgo.get_next_move();

    std::string moveStr(1, move);
    sim.logMsg("Algorithm chose to move: " + moveStr);

    if (move == 'F') {
      sim.moveForward();
    } else if (move == 'R') {
      sim.turnRight();
      sim.moveForward();
    } else if (move == 'L') {
      sim.turnLeft();
      sim.moveForward();
    } else if (move == 'U') {
      sim.turnAround();
      sim.moveForward();
    }
  }

  return 0;
}

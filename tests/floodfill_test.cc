#include "floodfill.h"

#include <cstdlib>
#include <iostream>

namespace
{
bool expect(bool condition, const char* message)
{
    if (!condition)
    {
        std::cerr << message << '\n';
    }
    return condition;
}
}  // namespace

int main()
{
    MM::Floodfill open_maze;

    if (!expect(open_maze.get_distance(7, 7) == 0,
                "center cells must have zero distance") ||
        !expect(open_maze.get_distance(0, 0) == 14,
                "start distance must match the shortest open-maze path") ||
        !expect(open_maze.count_straight_ahead() == 7,
                "northbound straight segment must end at the center row"))
    {
        return EXIT_FAILURE;
    }

    for (int move = 0; move < 14; ++move)
    {
        open_maze.set_sensor_data(false, false, false);
        open_maze.update();
        open_maze.get_next_move();
    }

    if (!expect(open_maze.is_searched(),
                "reaching a center cell must complete the search"))
    {
        return EXIT_FAILURE;
    }

    MM::Floodfill blocked_front;
    blocked_front.set_sensor_data(true, false, false);
    blocked_front.update();

    if (!expect(blocked_front.get_next_move() == 'R',
                "a north wall at the start must redirect the mouse east"))
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

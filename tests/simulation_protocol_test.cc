#include "mms.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

int main()
{
    std::istringstream input{"true false true ack"};
    std::ostringstream output;

    auto* original_input{std::cin.rdbuf(input.rdbuf())};
    auto* original_output{std::cout.rdbuf(output.rdbuf())};

    MM::Simulation simulation;
    const bool front{simulation.wallFront()};
    const bool right{simulation.wallRight()};
    const bool left{simulation.wallLeft()};
    simulation.moveForward();

    const bool responses_match{front && !right && left};
    const bool commands_match{output.str() ==
                              "wallFront\nwallRight\nwallLeft\nmoveForward\n"};

    simulation.wallFront();
    const bool eof_detected{!simulation.isConnected()};

    std::cin.rdbuf(original_input);
    std::cout.rdbuf(original_output);

    if (!responses_match || !commands_match || !eof_detected)
    {
        std::cerr << "MMS protocol handling failed\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

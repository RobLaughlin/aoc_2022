#include <iostream>
#include "RopeSimulation.h"

static const int NUM_KNOTS = 10;
static const int SIMULATION_WIDTH = 109;
static const int SIMULATION_HEIGHT = 51;
static const int FPS = 10;
static const std::string INPUT_FILENAME = "input.txt";

using std::cout;
using std::endl;

int main() {
    RopeSimulation sim(INPUT_FILENAME);

    sim.animate(NUM_KNOTS, cout, SIMULATION_WIDTH, SIMULATION_HEIGHT, FPS);
    return 0;
}
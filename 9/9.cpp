# include <iostream>
#include "Solution.h"
#include "RopeSimulation.h"

using std::cout;
using std::endl;

static const int NUM_KNOTS = 10;
static const int SIMULATION_WIDTH = 109;
static const int SIMULATION_HEIGHT = 51;
static const int FPS = 10;

int main() {
    Solution solution;

    cout << "Number of tail visits with 2 knots " << solution.num_tail_visits(2) << endl;
    cout << "Number of tail visits with 10 knots " << solution.num_tail_visits(10) << endl;

    RopeSimulation simulation(Solution::INPUT_FILENAME);
    simulation.animate(NUM_KNOTS, cout, SIMULATION_WIDTH, SIMULATION_HEIGHT, FPS);
    return 0;
}
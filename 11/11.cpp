#include "Solution.h"

static const int NUM_ROUNDS_1 = 20;
static const int NUM_ROUNDS_2 = 10000;

int main() {
    Solution sol;

    std::cout << "Monkey business over " << NUM_ROUNDS_1 << " rounds (without stress): ";
    std::cout << sol.monkey_business(NUM_ROUNDS_1, true) << std::endl;

    std::cout << "Monkey business over " << NUM_ROUNDS_2 << " rounds (with stress): ";
    std::cout << sol.monkey_business(NUM_ROUNDS_2, false) << std::endl;
    return 0;
}
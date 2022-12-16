#include "Solution.h"
#include <iostream>

static const int DEFAULT_SAND_SOURCE_X = 500;
static const int DEFAULT_SAND_SOURCE_Y = 0;

int main() {
    Solution14::Solution solution;
    std::cout << "Total sand fallen without a floor: ";
    std::cout << solution.find_sand_limit(DEFAULT_SAND_SOURCE_X, DEFAULT_SAND_SOURCE_Y, false) << std::endl;

    std::cout << "Total sand fallen with a floor: ";
    std::cout <<  solution.find_sand_limit(DEFAULT_SAND_SOURCE_X, DEFAULT_SAND_SOURCE_Y, true) << std::endl;
    return 0;
}
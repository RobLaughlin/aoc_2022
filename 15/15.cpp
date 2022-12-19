#include "Solution.h"
#include <iostream>

static const int MAX_ROW = 4000000;
static const int MIN_ROW = 0;
static const int TARGET_ROW = 2000000;

int main() {
    Solution15::Solution sol;
    std::cout << sol.positions_without_beacon(TARGET_ROW) << std::endl;
    std::cout << sol.tuning_frequency(MIN_ROW, MAX_ROW) << std::endl;
    return 0;
}
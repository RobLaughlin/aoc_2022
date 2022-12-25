#include "Solution.h"
#include <iostream>

int main() {
    Solution17::Solution sol;
    const int tower_width = 7;
    const long long num_rocks1 = 2022;
    const long long num_rocks2 = 1000000000000;
    const long long result1 = sol.tower_height(num_rocks1, tower_width);
    const long long result2 = sol.tower_height(num_rocks2, tower_width);

    std::cout << "Tower height with " << num_rocks1 << " rocks: " << result1 << std::endl;
    std::cout << "Tower height with " << num_rocks2 << " rocks: " << result2 << std::endl;
    return 0;
}
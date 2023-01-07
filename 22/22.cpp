#include "Solution.hpp"
#include <iostream>

int main() {
    Solution22::Solution sol(Solution22::Solution::AOC_INPUT);
    std::cout << "Password without cube wrapping: " << sol.find_password(false) << std::endl;
    std::cout << "Password with cube wrapping: " << sol.find_password(true) << std::endl;
    return 0;
}
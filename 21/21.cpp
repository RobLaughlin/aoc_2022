#include "Solution.hpp"
#include <iostream>

int main() {
    Solution21::Solution sol;
    std::cout << "The number the monkey root will yell: " << sol.root_yell() << std::endl;
    std::cout << "The number you have to yell: " << sol.find_human_number() << std::endl;
    return 0;
}
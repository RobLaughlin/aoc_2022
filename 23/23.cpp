#include "Solution.hpp"
#include <iostream>

int main() {
    Solution23::Solution sol;
    std::cout << sol.bounding_box_size(10) << std::endl;
    std::cout << sol.find_first_round() << std::endl;
    return 0;
}
#include "Solution.hpp"
#include <iostream>

int main() {
    Solution19::Solution sol;
    std::cout << "Calculating optimal quality... This could take a while..." << std::endl;
    std::cout << "Quality sum: " << sol.quality_sum(24) << std::endl;

    std::cout << "Calculating multiplied geodes... This could take a while..." << std::endl;
    std::cout << "Multiplied Geodes: " << sol.geode_multiplier(32) << std::endl;
    return 0;
}
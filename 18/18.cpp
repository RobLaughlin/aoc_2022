#include "Solution.h"
#include <iostream>

int main() {
    Solution18::Solution sol;
    std::cout << "Surface area of droplets including air pockets: " << sol.surface_area(true) << std::endl;
    std::cout << "Surface area of droplets not including air pockets: " << sol.surface_area(false) << std::endl;
    return 0;
}
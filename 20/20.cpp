#include "Solution.hpp"
#include <iostream>

int main() {
    const int MIXES = 10;
    const long long DEC_KEY = 811589153;

    Solution20::Solution sol;
    std::cout << "Grove Coordinate Sum with 1 mix and decryption key=1: ";
    std::cout << sol.grove_coord_sum(1, 1) << std::endl;

    std::cout << "Grove Coordinate Sum with " << MIXES << " mixes and decryption key=" << DEC_KEY << ": ";
    std::cout << sol.grove_coord_sum(MIXES, DEC_KEY) << std::endl;
    return 0;
}
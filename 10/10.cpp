#include "Solution.h"
#include <iostream>

int main() {
    Solution solution;

    std::cout << "Sum of signal strengths: " << solution.total_strengths() << std::endl << std::endl;
    std::cout << "CRT Image: " << std::endl << solution.generate_screen() << std::endl;
    return 0;
}
#include "Solution.h"
#include <iostream>

int main() {
    Solution solution;

    std::vector<int>* signals = solution.get_signal_strengths(20,40);

    int total = 0;
    for (int signal : *signals) {
        total += signal;
    }

    std::cout << total << std::endl;
    std::cout << solution.generate_image(40, 6) << std::endl;
    delete signals;
    return 0;
}
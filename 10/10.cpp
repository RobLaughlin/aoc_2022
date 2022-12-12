#include "Solution.h"
#include <iostream>

int main() {
    Solution solution;

    std::vector<int>* signals = solution.get_signal_strengths(20,40);

    int total = 0;
    for (int signal : *signals) {
        total += signal;
    }

    std::cout << total;
    delete signals;
    return 0;
}
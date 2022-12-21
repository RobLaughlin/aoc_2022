#include "Solution.h"
#include <iostream>

int main() {
    Solution16::Solution sol;
    std::unordered_map<std::string, long long> memo;

    const int time_bank = 30;

    int AA_index = 0;
    for (int i = 0; i < sol.valves.size(); i++) {
        if (sol.valves[i].ID == "AA") {
            AA_index = i;
            break;
        }
    }

    std::cout << sol.find_max_pressure(AA_index, time_bank, memo) << std::endl;
    return 0;
}
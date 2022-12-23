#include "Solution.h"
#include <iostream>

typedef Solution16::Solution::Path Path;
typedef Solution16::Solution::State State;

int main() {
    const int time_bank1 = 30;
    const int time_bank2 = 26;
    
    std::cout << "Computing all possible tunnel paths... This may take a while..." << std::endl;

    Solution16::Solution sol;
    std::unordered_map<std::string, long long> memo;

    int AA_index = 0;
    for (int i = 0; i < sol.valves.size(); i++) {
        if (sol.valves[i].ID == "AA") {
            AA_index = i;
            break;
        }
    }

    // Takes approximately an eternity to run... (5-10 minutes?)
    std::cout << "Max pressure by yourself in " << time_bank1 << " minutes: ";
    std::cout << sol.max_pressure(AA_index, time_bank1, false) << std::endl;

    std::cout << "Max pressure with help in " << time_bank2 << " minutes: ";
    std::cout << sol.max_pressure(AA_index, time_bank2, true) << std::endl;
    return 0;
}
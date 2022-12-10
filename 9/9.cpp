#include "Solution.h"

int main() {
    Solution solution;
    std::unordered_map<std::string, int>* tail_visits = solution.get_tail_visits();

    int visits = 0;
    for (auto const& kv : *tail_visits) {
        visits++;
    }
    
    std::cout << visits << std::endl;
    return 0;
}
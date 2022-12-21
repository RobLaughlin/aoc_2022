#pragma once
#include "Valve.h"
#include <vector>
#include <unordered_map>

namespace Solution16 {
    struct State {
        int current_valve;
        int time_remaining;
        std::unordered_set<int> opened;
    };

    class Solution {
    public:
        static const std::string INPUT_FILENAME;
        
        std::vector<Valve> valves;

        Solution();
        long long find_max_pressure(
            int valve_index, 
            int time_bank, 
            std::unordered_map<std::string, long long>& memo,
            std::unordered_set<int> opened=std::unordered_set<int>()
        ) const;

    private:
        std::string make_state_hash(const int& current_valve, const int& time_bank, const std::unordered_set<int>& opened) const;
    };
};

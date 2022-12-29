#pragma once
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include "Blueprint.hpp"
#include "GameState.hpp"

namespace Solution19 {
    class Solution {
    public:
        typedef std::unordered_map<std::string, long long> StateMap;

        static const std::string INPUT_FILENAME;

        Solution();
        long long quality_sum(long long time_remaining) const;
        long long geode_multiplier(long long time_remaining) const;
    private:
        std::vector<Blueprint> blueprints;
        
        // Use BFS to iterate over all the game states and find the largest number of geodes/quality
        long long find_max_geodes(int blueprint_id, long long time_remaining) const;
    };
};
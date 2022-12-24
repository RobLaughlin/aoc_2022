#pragma once
#include "Rock.h"
#include <vector>

namespace Solution17 {
    class Solution {
    public:
        static const std::string INPUT_FILENAME;
        enum RockType {BAR, CROSS, L, LINE, SQUARE};
        
        Solution();

        // Get the height of the tower after num_rocks fall
        long long tower_height(long long num_rocks, int tower_width) const;

    private:
        static const std::vector<Rocks::Rock> m_ROCKS;
        std::string m_jetstream;
    };
};
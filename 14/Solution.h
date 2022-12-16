#pragma once
#include <string>
#include <unordered_map>
#include "HPair.h"

namespace Solution14 {
    class Solution {
    public:
        typedef std::unordered_map<HPair::IIPair, char> CoordMap;

        static const std::string INPUT_FILENAME;
        Solution();
        int find_sand_limit(int sand_source_x, int sand_source_y, bool has_floor) const;
    private:
        CoordMap coord_map;

        void parse_line(std::string line);
    };
};


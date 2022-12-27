#pragma once
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include "HashableTuple.h"

namespace Solution18 {
    class Solution {
    public:
        typedef HTuple<int, int, int> Cube;
        typedef std::unordered_map<Cube, std::unordered_set<Cube>> CubeMap;

        static const std::string INPUT_FILENAME;

        Solution();
        int surface_area(bool include_air_pockets) const;
    private:
        CubeMap cubes;
        std::pair<int, int> x_bounds;
        std::pair<int, int> y_bounds;
        std::pair<int, int> z_bounds;

        static std::vector<Cube> get_neighbors(const Cube& cube);
        bool is_air_pocket(const Cube& cube) const;
    };
};
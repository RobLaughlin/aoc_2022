#pragma once
#include <string>
#include "../data_structures/Grid.h"

class Solution {
public:
    static const std::string INPUT_FILENAME;
    Solution();
    int shortest_path(char start_elevation='S') const;
private:
    int shortest_path(int start_row, int start_col) const;
    Grid<char> heightmap;
};
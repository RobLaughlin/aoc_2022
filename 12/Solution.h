#pragma once
#include <string>
#include "../data_structures/Grid.h"

class Solution {
public:
    static const std::string INPUT_FILENAME;
    Solution();
    int shortest_path() const;
private:
    Grid<char> heightmap;
};
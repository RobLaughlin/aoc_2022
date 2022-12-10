#pragma once
#include <string>
#include <utility>
#include "Grid.h"

class Solution{ 
public:
    enum Direction {TOP, RIGHT, LEFT, DOWN};

    static const std::string INPUT_FILENAME;
    Solution();
    int count_visible() const;
    int scenic_score(int row, int col) const;
    int max_scenic_score() const;
private:
    static std::pair<int, int> grid_dims();
    void apply_visibility_mask(Grid<bool>& mask, Direction direction) const;
    Grid<int> grid;
};
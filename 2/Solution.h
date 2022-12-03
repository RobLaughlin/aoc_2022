#pragma once
#include <string>
#include <vector>
#include <array>
#include "Game.h"

class Solution {
public:
    // Preprocessing step
    Solution(const std::string& input_filename);

    // returns [solution to pt 1, solution to pt 2] 
    std::array<int, 2> solve();
private:
    std::vector<Game> games;
};
#pragma once
#include <string>
#include <fstream>
#include <queue>
#include <unordered_set>

class Solution {
public:
    Solution(const std::string& input_file);
    int find_marker(int preamble_length);
private:
    std::string signal;
};
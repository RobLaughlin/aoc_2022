#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <regex>
#include <iostream>
#include "RangePair.h"

class Solution {
public:
    Solution(const std::string& input_file);
    int num_containments();
    int num_overlaps();
private:
    static const std::regex MATCH_DIGIT;
    std::vector<RangePair> pairs;
};
#pragma once
#include <vector>
#include <string>
#include <limits>

class Solution {
public:
    Solution(const std::string input_filepath);

    // Return the calorie sum from the top n elves
    int MaxCalories(const int n);
private:
    std::vector<int> calories;

    // Find the minimum element in a vector, and return the index of that minimum element.
    static int min_index(const std::vector<int>& arr, const int &length);
};
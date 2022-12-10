#pragma once
#include <string>
#include <fstream>
#include <utility>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <cmath>

class Solution {
public:
    static const std::string INPUT_FILENAME;
    Solution();
    std::unordered_map<std::string, int>* get_tail_visits(int num_knots=1) const;
    int num_tail_visits(int num_knots=1) const;
private:
    std::vector<std::pair<char, int>> moves;
    void update_tail(const std::pair<int, int>& head_pos, std::pair<int, int>& tail_pos) const;

    template <typename T>
    static std::string pair_to_string(std::pair<T, T> pair);

    template <typename T>
    static double pair_dist(std::pair<T, T> pair1, std::pair<T, T> pair2);

};
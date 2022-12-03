#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <unordered_set>

class Solution {
    typedef std::string Rucksack;

public:
    Solution(const std::string& input_file);
    int common_pair(); // Solution to part 1
    int common_group(); // Solution to part 2
private:
    std::vector<Rucksack> rucksacks;

    // In a list of rucksacks (strings), find a common character in al of them
    char common_char(const std::vector<Rucksack>& rucksacks);

    static int char_priority(const char& c);

    // Intersect two unordered sets together
    template <typename T> static std::unordered_set<T> intersect_sets(
        const std::unordered_set<T>& s1, const std::unordered_set<T>& s2
    );
};
#pragma once
#include <string>
#include <unordered_set>
#include <tuple>
#include <utility>
#include <boost/functional/hash.hpp>

namespace Solution23 {
    class Solution {
    public:
        typedef std::tuple<int, int> Elf;
        typedef std::pair<Elf, Elf> Proposal;
        static const std::string INPUT_FILENAME;

        Solution();
        int bounding_box_size(long long rounds) const;
        int find_first_round() const;
    private:
        std::unordered_set<Elf, boost::hash<Elf>> elves;
    };
};
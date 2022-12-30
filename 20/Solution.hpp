#pragma once
#include <string>
#include <vector>

namespace Solution20 {
    class Solution {
    public:
        typedef long long llong;

        static const std::string INPUT_FILENAME;

        Solution();
        llong grove_coord_sum(llong num_mixes=1, llong decryption_key=1) const;
    private:
        std::vector<llong> m_nums;

        std::vector<llong> mix_nums(llong num_mixes, llong decryption_key) const;
    };
};
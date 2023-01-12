#pragma once
#include <string>
#include <vector>

namespace Solution25 {
    class Solution {
    public:
        static const std::string INPUT_FILENAME;

        Solution();
        std::string find_snafu_number() const;
    private:
        std::vector<std::string> m_snafu_nums;

        long long snafu2dec(std::string snafu_num) const;
        std::string dec2snafu(long long) const;
    };
};
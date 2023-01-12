#include "Solution.hpp"
#include <fstream>
#include <math.h>
#include <sstream>
#include <stack>
using namespace Solution25;

const std::string Solution::INPUT_FILENAME = "input.txt";

Solution::Solution() {
    std::ifstream input(INPUT_FILENAME);

    std::string line;
    while (std::getline(input, line)) {
        this->m_snafu_nums.push_back(line);
    }
}

std::string Solution::find_snafu_number() const {
    long long total = 0;
    for (const std::string& snafu_num : this->m_snafu_nums) {
        total += snafu2dec(snafu_num);
    }
    return dec2snafu(total);
}

long long Solution::snafu2dec(std::string snafu_num) const {
    long long n = 0;
    int last_digit_idx = snafu_num.length()-1;
    for (int i = last_digit_idx; i >= 0; i--) {
        const char& c = snafu_num[i];
        switch (c) {
            case '0':
            case '1':
            case '2':
                n += (c - '0')*std::pow(5, last_digit_idx-i); break;
            case '-':
                n += -1*std::pow(5, last_digit_idx-i); break;
            case '=':
                n += -2*std::pow(5, last_digit_idx-i); break;
        }
    }
    return n;
}

std::string Solution::dec2snafu(long long decimal) const {
    std::stack<char> tokens;
    while (decimal != 0) {
        long long digit = decimal % 5;
        switch (digit) {
            case 0:
            case 1:
            case 2:
                tokens.push((char)(digit+'0')); 
                break;
            case 3:
                tokens.push('=');
                digit = -2;
                break;
            case 4:
                tokens.push('-'); 
                digit = -1;
                break;
        }
        decimal = (decimal - digit) / 5;
    }

    // Reverse the string
    std::stringstream snafu;
    while (!tokens.empty()) {
        snafu << tokens.top();
        tokens.pop();
    }

    return snafu.str();
}
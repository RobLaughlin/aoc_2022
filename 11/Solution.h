#pragma once
#include <string>
#include "Monkey.h"

class Solution {
public:
    static const std::string INPUT_FILENAME;

    Solution();
    long long monkey_business(int rounds, bool manage_stress) const;
private:
    long long divisibility_product;
    std::vector<Monkey> monkeys;
};
#pragma once
#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include <regex>
#include <array>
#include "InstructionStack.h"

class Solution {
public:
    Solution(const std::string& input_file);
    std::string one_at_a_time();
    std::string some_at_a_time();
private:
    InstructionStack start_stack;
    InstructionStack instruction_stack;
};
#pragma once
#include <string>
#include <vector>
#include "TimedInstruction.h"

class Solution {
public:
    static const std::string INPUT_FILENAME;

    Solution();
    const std::vector<TimedInstruction>& get_instructions() const;
    std::vector<int>* register_values() const;
    std::vector<int>* get_signal_strengths(int start, int on_cycle) const;
    std::string generate_image(int width, int height) const;
private:
    std::vector<TimedInstruction> instructions;
};

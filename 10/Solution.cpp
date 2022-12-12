#include "Solution.h"
#include <fstream>
#include <unordered_map>
#include <string>
#include <queue>

#include <iostream>

const std::string Solution::INPUT_FILENAME = "input.txt";

Solution::Solution() {
    std::ifstream input(INPUT_FILENAME);

    std::string line;
    while (std::getline(input, line)) {
        int timing = 1;
        int quantity = 0;
        
        if (line.substr(0, 4) == "addx") {
            quantity = std::stoi(line.substr(5));
            timing = 2;
        }

        this->instructions.push_back(TimedInstruction(timing, quantity));
    }
}

const std::vector<TimedInstruction>& Solution::get_instructions() const {
    return this->instructions;
}

std::vector<int>* Solution::get_signal_strengths(int start, int on_cycle) const {
    std::vector<int>* strengths = new std::vector<int>();
    int x = 1;
    int cycle = 1;

    for (const TimedInstruction& ti : this->instructions) {
        for (int i = 1; i < ti.timing; i++) {
            if (cycle + i >= start && (cycle + i -start) % on_cycle == 0) {
                strengths->push_back(x*(cycle+i));
            }
        }
        cycle += ti.timing;
        x += ti.quantity;

        if (cycle >= start && (cycle - start) % on_cycle == 0) {
            strengths->push_back(x*cycle);
        }
        
    }

    // std::vector<int> additions(2*this->instructions.size(), 0);

    // for (int i = 0; i < additions.size(); i++) {
        
    //     if (2*i+1 >= start && (2*i+1-start) % on_cycle == 0) {
    //         std::cout << x << std::endl;
    //     }
    //     if (i < this->instructions.size()) {
    //         int qty = this->instructions[i].quantity;
    //         int timing = this->instructions[i].timing;
    //         additions[i+timing] += qty;
    //     }

    //     x += additions[i];
    //     // std::cout << x << std::endl << std::endl;
    // }
    return strengths;
}
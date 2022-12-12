#include "Solution.h"
#include <fstream>
#include <unordered_map>
#include <string>
#include <queue>
#include <sstream>
#include "../data_structures/Grid.h"

const std::string Solution::INPUT_FILENAME = "input.txt";
const int Solution::SIGNAL_START = 20;
const int Solution::SIGNAL_CYCLE = 40;
const int Solution::CRT_WIDTH = 40;
const int Solution::CRT_HEIGHT = 6;

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

int Solution::total_strengths() const {
    std::vector<int>* strengths = this->get_signal_strengths(SIGNAL_START, SIGNAL_CYCLE);

    int total = 0;
    for (int strength : *strengths) {
        total += strength;
    }

    delete strengths;
    return total;
}

std::string Solution::generate_screen() const {
    return this->generate_image(CRT_WIDTH, CRT_HEIGHT);
}

const std::vector<TimedInstruction>& Solution::get_instructions() const {
    return this->instructions;
}

std::vector<int>* Solution::register_values() const {
    std::vector<int>* values = new std::vector<int>();
    int x = 1;
    int cycle = 1;

    for (const TimedInstruction& ti : this->instructions) {
        for (int i = 1; i < ti.timing; i++) {
            values->push_back(x);
        }
        cycle += ti.timing;
        x += ti.quantity;
        values->push_back(x);
    }

    return values;
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

    return strengths;
}

std::string Solution::generate_image(int width, int height) const {
    std::vector<int>* values = register_values();
    Grid<char> CRT(height, width, '.');

    int pixel_row = 0;
    int pixel_col = 0;
    for (const int& x : *values) {
        // std::cout << CRT << std::endl;
        // std::cout << x << std::endl;
        if (x == pixel_col || x == pixel_col+1 || x == pixel_col+2) {
            CRT.place('#', pixel_row, pixel_col);
        }
        
        pixel_col++;
        if (pixel_col == width) {
            pixel_col = 0;
            pixel_row++;
        }
    }
    delete values;

    std::stringstream img;
    img << CRT;

    return img.str();
}
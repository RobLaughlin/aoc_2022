#pragma once
#include <string>
#include <iostream>
#include <unordered_set>

class Rucksack {
public:
    Rucksack(const std::string& rucksack);
    char find_common_letter();
    static int char_priority(const char c);
    friend std::ostream& operator<<(std::ostream& os, const Rucksack& rucksack);
private:
    std::string left_compartment;
    std::string right_compartment;
};
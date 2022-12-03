#include "Rucksack.h"

Rucksack::Rucksack(const std::string& rucksack) {
    if (rucksack.size() % 2 != 0) { 
        throw std::invalid_argument("Rucksack string must have an even number of characters.");
    }

    const int midpt = rucksack.size() / 2;
    this->left_compartment = rucksack.substr(0, midpt);
    this->right_compartment = rucksack.substr(midpt, rucksack.size());
}

char Rucksack::find_common_letter() {
    std::unordered_set<char> Lcompartment = std::unordered_set<char>();

    for (char c : this->left_compartment) {
        Lcompartment.insert(c);
    }

    for (char c : this->right_compartment) {
        if (Lcompartment.count(c) > 0) { return c; }
    }

    return '\0';
}

int Rucksack::char_priority(const char c) {
    int ascii_c = int(c);
    if (ascii_c >= int('A') && ascii_c <= int('Z')) {
        return ascii_c - int('A') + 27;
    }
    else if (ascii_c >= int('a') && ascii_c <= int('z')) {
        return ascii_c - int('a') + 1;
    }
    else {
        return 0;
    }
}

std::ostream& operator<<(std::ostream& os, const Rucksack& rucksack) {
    os << '(' << rucksack.left_compartment << ", " << rucksack.right_compartment << ')';
    return os;
}
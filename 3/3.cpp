#include <iostream>
#include <fstream>
#include <vector>
#include "Rucksack.h"
using namespace std;

static const string INPUT_FILENAME = "input.txt";

vector<Rucksack> preprocess(const string& input_file) {
    vector<Rucksack> rucksacks = vector<Rucksack>();

    ifstream input;
    input.open(input_file);
    if (!input.is_open()) {
        throw invalid_argument("Input file could not be opened");
    }

    string line;
    while (getline(input, line)) {
        rucksacks.push_back(Rucksack(line));
    }
    input.close();

    return rucksacks;
}

int main() {
    vector<Rucksack> rucksacks = preprocess(INPUT_FILENAME);

    int priorities = 0;
    for (Rucksack r : rucksacks) {
        priorities += Rucksack::char_priority(r.find_common_letter());
    }
    cout << priorities;

    vector<Rucksack> group_rucksacks = vector<Rucksack>();
    
    return 0;
}
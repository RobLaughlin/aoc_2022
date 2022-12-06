#include "Solution.h"

Solution::Solution(const std::string& input_file) {
    std::ifstream input;
    input.open(input_file);

    if (!input.is_open()) {
        throw std::invalid_argument("Error opening input file");
    }

    std::getline(input, this->signal);
}

int Solution::find_marker(int preamble_length) {
    std::queue<char> q = std::queue<char>();
    std::unordered_set<char> checked = std::unordered_set<char>();

    for (int i = 0; i < this->signal.length(); i++) {
        const char c = this->signal[i];

        // Check if we found our unique character sequence
        if (checked.find(c) == checked.end() && q.size() == preamble_length-1) {
            return i+1;
        }

        // If we found a duplicate, remove everything from the queue until we hit the dupe letter.
        while (checked.find(c) != checked.end()) {
            checked.erase(q.front());
            q.pop();
        }

        checked.insert(c);
        q.push(c);
    }

    return -1;
}
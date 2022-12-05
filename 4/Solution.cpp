#include "Solution.h"

const std::regex Solution::MATCH_DIGIT = std::regex("-?\\d+");

Solution::Solution(const std::string& input_file) {
    std::ifstream input;
    input.open(input_file);
    if (!input.is_open()) {
        throw std::invalid_argument("Error reading input file " + input_file);
    }

    this->pairs = std::vector<RangePair>();
    std::string line;
    while (std::getline(input, line)) {
        std::smatch match;
        Range r1;
        Range r2;

        std::regex_search(line, match, MATCH_DIGIT);
        r1.min = stoi(match.str());
        line = match.suffix().str();
        
        regex_search(line, match, MATCH_DIGIT);
        r1.max = -stoi(match.str());
        line = match.suffix().str();

        regex_search(line, match, MATCH_DIGIT);
        r2.min = stoi(match.str());
        line = match.suffix().str();

        regex_search(line, match, MATCH_DIGIT);
        r2.max = -stoi(match.str());
        line = match.suffix().str();

        RangePair p ={r1, r2};
        this->pairs.push_back(p);
    }
}

int Solution::num_containments() {
    int containments = 0;

    for (RangePair pair : this->pairs) {
        if (pair.hasContainment()) { containments++; }
    }

    return containments;
}

int Solution::num_overlaps() {
    int overlaps = 0;

    for (RangePair pair : this->pairs) {
        if (pair.hasOverlap()) { overlaps++; }
    }

    return overlaps;
}
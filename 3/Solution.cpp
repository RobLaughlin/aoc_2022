#include "Solution.h"

Solution::Solution(const std::string& input_file) {
    this->rucksacks = std::vector<Rucksack>();

    std::ifstream input;
    input.open(input_file);
    if (!input.is_open()) {
        throw std::invalid_argument("Input file could not be opened");
    }

    std::string line;
    while (std::getline(input, line)) {
        this->rucksacks.push_back(line);
    }
    input.close();
}

int Solution::common_pair() {
    // Split each rucksack into halves and find the common character between them
    int sum_priorities = 0;

    for (Rucksack r : this->rucksacks) {
        const int mid = r.size()/2;
        const Rucksack Lhalf = r.substr(0, mid);
        const Rucksack Rhalf = r.substr(mid, r.size());
        const std::vector<Rucksack> parts = {Lhalf, Rhalf};
        const char c = common_char(parts);
        sum_priorities += char_priority(c);
    }
    return sum_priorities;
}

int Solution::common_group() {
    // Organize rucksacks into groups of 3.
    // Whenever we get a full group of 3, find the common character in all of them,
    // then convert that common character to its priority and add it to the total priorities.
    int sum_priorities = 0;
    int k = 1;

    std::vector<Rucksack> group = std::vector<Rucksack>();
    for (Rucksack r : this->rucksacks) {
        group.push_back(r);
        if (k % 3 == 0) {
            const char c = common_char(group);
            sum_priorities += char_priority(c);
            k = 0;
            group = std::vector<Rucksack>();
        }
        k++;
    }
    return sum_priorities;
}

int Solution::char_priority(const char& c) {
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

char Solution::common_char(const std::vector<Rucksack>& rucksacks) {
    // Use consecutive set intersections to find the common character in the list of rucksacks
    
    std::unordered_set<char> common_chars (rucksacks[0].begin(), rucksacks[0].end());
    for (int i = 1; i < rucksacks.size(); i++) {
        const Rucksack rucksack = rucksacks[i];
        std::unordered_set<char> to_intersect (rucksack.begin(), rucksack.end());
        common_chars = intersect_sets(common_chars, to_intersect);
    }

    if (common_chars.empty()) { return '\0'; }
    return *common_chars.begin();
}

template <typename T> 
std::unordered_set<T> Solution::intersect_sets(const std::unordered_set<T>& s1, const std::unordered_set<T>& s2) {
    std::unordered_set<T> intersected = std::unordered_set<T>();
    std::unordered_set<T> min_set = s1.size() <= s2.size() ? s1 : s2;
    std::unordered_set<T> max_set = s1.size() <= s2.size() ? s2 : s1;

    for (auto it = min_set.begin(); it != min_set.end(); ++it) {
        T elem = *it;
        if (max_set.count(elem) > 0 && intersected.count(elem) == 0) {
            intersected.insert(elem);
        }
    }

    return intersected;
}


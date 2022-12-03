#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

typedef string Rucksack;
static const string INPUT_FILENAME = "input.txt";

static vector<Rucksack> preprocess(const string& input_file) {
    vector<Rucksack> rucksacks = vector<Rucksack>();

    ifstream input;
    input.open(input_file);
    if (!input.is_open()) {
        throw invalid_argument("Input file could not be opened");
    }

    string line;
    while (getline(input, line)) {
        rucksacks.push_back(line);
    }
    input.close();

    return rucksacks;
}

template <typename T>
static unordered_set<T> intersect_sets(unordered_set<T> s1, unordered_set<T> s2) {
    unordered_set<T> intersected = unordered_set<T>();
    unordered_set<T> min_set = s1.size() <= s2.size() ? s1 : s2;
    unordered_set<T> max_set = s1.size() <= s2.size() ? s2 : s1;

    for (auto it = min_set.begin(); it != min_set.end(); ++it) {
        T elem = *it;
        if (max_set.count(elem) > 0 && intersected.count(elem) == 0) {
            intersected.insert(elem);
        }
    }

    return intersected;
}

static char common_char(const vector<Rucksack>& rucksacks) {
    unordered_set<char> common_chars (rucksacks[0].begin(), rucksacks[0].end());
    for (int i = 1; i < rucksacks.size(); i++) {
        const Rucksack rucksack = rucksacks[i];
        unordered_set<char> to_intersect (rucksack.begin(), rucksack.end());
        common_chars = intersect_sets(common_chars, to_intersect);
    }

    if (common_chars.empty()) { return '\0'; }
    return *common_chars.begin();
}

int char_priority(const char& c) {
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

int main() {
    vector<Rucksack> rucksacks = preprocess(INPUT_FILENAME);

    int sum_priorities = 0;
    for (Rucksack r : rucksacks) {
        const int mid = r.size()/2;
        const Rucksack Lhalf = r.substr(0, mid);
        const Rucksack Rhalf = r.substr(mid, r.size());
        const vector<Rucksack> parts = {Lhalf, Rhalf};
        const char c = common_char(parts);
        sum_priorities += char_priority(c);
    }

    cout << sum_priorities << endl;

    sum_priorities = 0;
    vector<Rucksack> group = vector<Rucksack>();
    int k = 1;
    for (Rucksack r : rucksacks) {
        group.push_back(r);
        if (k % 3 == 0) {
            const char c = common_char(group);
            sum_priorities += char_priority(c);
            k = 0;
            group = vector<Rucksack>();
        }
        k++;
    }
    cout << sum_priorities << endl;
    return 0;
}
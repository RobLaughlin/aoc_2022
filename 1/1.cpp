#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <numeric>
#include "1.h"

using namespace std;

const string INPUT_FILE = "input.txt";

int Solution::min_index(const std::vector<int>& arr, const int &length) {
    int idx = -1;
    int min = std::numeric_limits<int>::max();

    for (int i = 0; i < length; i++) {
        if (arr[i] < min) {
            min = arr[i];
            idx = i;
        }
    }
    return idx;
}

Solution::Solution(const string input_filepath) {
    this->calories = vector<int>();
    
    ifstream input;
    input.open(input_filepath);
    if (!input.is_open()) {
        cerr << "Error opening " << INPUT_FILE << "..." << endl;
        input.close();
        return;
    }

    int total = 0;
    string line;
    while (getline(input, line)) {
        if (line == "") {
            this->calories.push_back(total);
            total = 0;
        }
        else {
            total += stoi(line);
        }
    }

    if (total > 0) { this->calories.push_back(total); }
    input.close();
}

int Solution::MaxCalories(const int n) {
    vector<int> top (n, 0);
    int maxCalories = 0;

    for (const int calorie : this->calories) {
        const int m = this->min_index(top, n);
        top[m] = calorie > top[m] ? calorie : top[m];
    }
    return reduce(top.begin(), top.end());
}

int main() {
    Solution sol = Solution(INPUT_FILE);

    cout << "Max Calories" << endl;
    cout << sol.MaxCalories(1) << endl << endl;

    cout << "Total Max Calories from 3 Elves" << endl;
    cout << sol.MaxCalories(3) << endl << endl;
    return 0;
}
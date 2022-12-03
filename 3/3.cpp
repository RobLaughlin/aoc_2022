#include <string>
#include <iostream>
#include "Solution.h"

using std::string;
using std::cout;
using std::endl;

static const string INPUT_FILENAME = "input.txt";

int main() {
    Solution solution = Solution(INPUT_FILENAME);
    const int common_pair = solution.common_pair();
    const int common_group = solution.common_group();

    cout << "Common character in each half of a rucksack: " << common_pair << endl;
    cout << "Common character in each 3-rucksack group: " << common_group << endl;
    return 0;
}
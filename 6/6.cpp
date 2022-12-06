#include <iostream>
#include "Solution.h"

using std::cout;
using std::endl;

static const int PREAMBLE_LENGTH_1 = 4;
static const int PREAMBLE_LENGTH_2 = 14;
static const std::string INPUT_FILENAME = "input.txt";

int main() {
    Solution solution = Solution(INPUT_FILENAME);

    cout << "start-of-packet marker is at index: " << solution.find_marker(PREAMBLE_LENGTH_1) << endl;
    cout << "start-of-message marker is at index: " << solution.find_marker(PREAMBLE_LENGTH_2) << endl;
    return 0;
}
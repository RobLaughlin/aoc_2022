#include <iostream>
#include "Solution.h"

using std::cout;
using std::endl;

static const std::string INPUT_FILENAME = "input.txt";

int main() {
    Solution solution = Solution(INPUT_FILENAME);

    cout << "Tops of stacks moving 1 block at a time: " << solution.one_at_a_time() << endl;
    cout << "Tops of stacks moving multiple blocks at a time: " << solution.some_at_a_time() << endl;
    return 0;
}
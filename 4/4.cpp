#include "Solution.h"

using std::cout;
using std::endl;

static const std::string INPUT_FILENAME = "input.txt";

int main() {
    Solution solution = Solution(INPUT_FILENAME);

    cout << "Total number of containments: " << solution.num_containments() << endl;
    cout << "Total number of overlaps: " << solution.num_overlaps() << endl;
    return 0;
}
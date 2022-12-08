#include "Solution.h"

static const std::string INPUT_FILENAME = "input.txt";
static const size_t MAX_SIZE = 100000;
static const size_t FILESYSTEM_SIZE = 70000000;
static const size_t SPACE_NEEDED = 30000000;

using std::cout;
using std::endl;

int main() {
    Solution solution = Solution(INPUT_FILENAME, FILESYSTEM_SIZE);
    cout << *solution.root << endl;
    cout << "Sum of directory sizes under " << MAX_SIZE << ": " << solution.sum_dir_sizes(MAX_SIZE) << endl;
    cout << "Size of the smallest directory required to achieve the space requirement: ";
    cout << solution.smallest_dir_size(SPACE_NEEDED) << endl;

    return 0;
}
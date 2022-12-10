#include "Solution.h"

using std::cout;
using std::endl;

int main() {
    Solution solution = Solution();
    cout << "Number of trees visible from edges: " << solution.count_visible() << endl;
    cout << "Maximum scenic score of the trees: " << solution.max_scenic_score() << endl;
    return 0;
}
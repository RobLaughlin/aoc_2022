#include <string>
#include "Solution.h"

using namespace std;

const string INPUT_FILENAME = "input.txt";

int main() {
    Solution solution = Solution(INPUT_FILENAME);
    array<int, 2> result = solution.solve();

    cout << "\nTotal score from choosing my move based on the strategy guide (Part 1)" << endl;
    cout << result[0] << endl << endl; 

    cout << "Total score from choosing how I should win/lose/draw based on the strategy guide (Part 2)" << endl;
    cout << result[1] << endl;
    return 0;
}
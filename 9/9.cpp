# include <iostream>
#include "Solution.h"

using std::cout;
using std::endl;

int main() {
    Solution solution;

    cout << "Number of tail visits with 2 knots " << solution.num_tail_visits(2) << endl;
    cout << "Number of tail visits with 10 knots " << solution.num_tail_visits(10) << endl;
    return 0;
}
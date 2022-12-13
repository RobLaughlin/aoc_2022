#include "Solution.h"

int main() {
    Solution sol = Solution();
    std::cout << "Shortest path starting at elevation S: " << sol.shortest_path() << std::endl;
    std::cout << "Shortest path starting at elevation a: " << sol.shortest_path('a') << std::endl;
    return 0;
}
#include "Solution.hpp"
#include <iostream>



int main() {
    typedef Solution24::Solution::Coord Coord;

    Solution24::Solution sol;
    std::pair<Coord, Coord> endpoints = sol.get_endpoints();
    const Coord& top = endpoints.first;
    const Coord& bottom = endpoints.second;

    int fewest_minutes = sol.fewest_minutes(top, bottom);
    std::cout << "Finding minimum distances, this may take a while..." << std::endl;
    std::cout << "Minimum minutes spent from top to bottom: " << fewest_minutes << std::endl;
    fewest_minutes += sol.fewest_minutes(bottom, top);
    fewest_minutes += sol.fewest_minutes(top, bottom);
    std::cout<< "Minimum minutes spent from top->bottom->top->bottom: " << fewest_minutes << std::endl;
    return 0;
}
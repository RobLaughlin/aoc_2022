#pragma once
#include <utility>

struct Blueprint
{
    Blueprint(int ore_cost, int clay_cost, std::pair<int, int> obsidian_cost, std::pair<int, int> geode_cost);
    int ore_cost;
    int clay_cost;
    std::pair<int, int> obsidian_cost;
    std::pair<int, int> geode_cost;
};
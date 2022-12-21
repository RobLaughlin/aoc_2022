#pragma once
#include <string>
#include <unordered_set>

struct Valve {
    std::string ID;
    int flow_rate;
    const std::unordered_set<int> connected;

    Valve();
    Valve(std::string ID, int flow_rate, std::unordered_set<int> connected);
};
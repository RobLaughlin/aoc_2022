#include "Valve.h"

Valve::Valve() 
    : ID("--"), flow_rate(0), connected(std::unordered_set<int>()) {}

Valve::Valve(std::string ID, int flow_rate, std::unordered_set<int> connected) 
    : ID(ID), flow_rate(flow_rate), connected(connected) {}
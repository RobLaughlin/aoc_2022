#pragma once
#include "../Grid.h"

class SimulationGrid : Grid<char> {
public:
    using Grid<char>::Grid;
    using Grid<char>::place;
    friend std::ostream& operator<<(std::ostream& os, const SimulationGrid& other);
};
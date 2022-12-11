#include "SimulationGrid.h"

std::ostream& operator<<(std::ostream& os, const SimulationGrid& other) {
    for (unsigned int r = 0; r < other.rows; r++) {
        for (unsigned int c = 0; c < other.cols; c++) {
            os << other.at(r, c);
        }
        os << std::endl;
    }
    return os;
}
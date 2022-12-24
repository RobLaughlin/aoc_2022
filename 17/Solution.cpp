#include "Solution.h"
#include <fstream>
#include <math.h>
#include <iostream>

using namespace Solution17;

const std::string Solution::INPUT_FILENAME = "input.txt";
const std::vector<Rocks::Rock> Solution::m_ROCKS = {
    Rocks::Bar(), 
    Rocks::Cross(),
    Rocks::L(), 
    Rocks::Line(), 
    Rocks::Square()
};

Solution::Solution() {
    std::ifstream input(INPUT_FILENAME);
    std::getline(input, this->m_jetstream);
}

long long Solution::tower_height(long long num_rocks, int tower_width) const {
    if (tower_width % 2 == 0 || tower_width < 0) {
        throw std::invalid_argument("Tower width must be odd and positive");
    }

    RockType current_rock = BAR;    // Index of rock vector
    int current_jet = 0;            // Index of jetstream string
    long long max_height = 0;             // Maximum height of the tower

    // Keep track of all rocks that hit the ground
    Rocks::CoordSet terrain;

    // Add the floor to the terrain
    for (int i = -(tower_width-1)/2; i < (tower_width-1)/2; i++) {
        terrain.insert(Rocks::Coord(i, 0));
    }

    // Add walls to the terrain
    for (int i = 0; i < 4*(num_rocks+2); i++) {
        int xl = -(tower_width+1)/2;
        int xr = -xl;

        terrain.insert(Rocks::Coord(xl, i));
        terrain.insert(Rocks::Coord(xr, i));
    }

    while (num_rocks > 0) {
        // Spawn a new rock at the center of the tower
        Rocks::Rock rock = this->m_ROCKS[current_rock];

        // Set spawn position of rock 3 units above the previous rock
        bool collision = rock.translate(0, max_height+4, terrain);

        // Keep iterating until we collide with another rock in our terrain
        while (!collision) {
            char jet_direction = this->m_jetstream[current_jet] == '<' ? -1 : 1;
            current_jet = (current_jet + 1) % (this->m_jetstream.size());

            rock.translate(jet_direction, 0, terrain);
            collision = rock.translate(0, -1, terrain);
        }
        
        // We reach a collision, the rock becomes a part of the terrain
        for (const auto& coord : rock) {
            terrain.insert(coord);
            max_height = std::max(max_height, coord.second);
        }

        // Switch to the next rock
        current_rock = (RockType)(((int)(current_rock) + 1) % 5);
        num_rocks--;
    }

    return max_height;
}
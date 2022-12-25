#include "Solution.h"
#include <fstream>
#include <math.h>
#include <sstream>
#include <unordered_map>
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
    long long current_jet = 0;      // Index of jetstream string
    long long max_height = 0;       // Maximum height of the tower

    // Cache the surface of the tower
    std::vector<long long> current_surface = std::vector<long long>();

    // Add the repeated height values
    long long rep_height = 0;

    std::unordered_map<std::string, Rocks::Coord> heightmap;

    // Keep track of all rocks that hit the ground
    Rocks::CoordSet terrain;

    // Add the floor to the terrain
    for (int i = -(tower_width-1)/2; i <= (tower_width-1)/2; i++) {
        terrain.insert(Rocks::Coord(i, 0));
        current_surface.push_back(0);
    }

    long long num_walls = 0;
    while (num_rocks > 0) {
        std::string key = this->hash_state(current_rock, current_surface, current_jet, max_height);

        // Check if we've been here before
        if (heightmap.find(key) == heightmap.end()) {
            heightmap[key] = Rocks::Coord(max_height, num_rocks);
        }
        else {
            // If we have been here before, add as many repeated cycles as we can
            const long long& prev_height = heightmap[key].first;
            const long long& prev_rocks = heightmap[key].second;

            const long long fallen = std::abs(num_rocks - prev_rocks);
            const long long dh = max_height - prev_height;
            rep_height += dh*(std::floor(num_rocks / fallen));
            num_rocks = num_rocks % fallen;
        }

        // Add walls to the terrain
        for (long long i = num_walls; i < num_walls+10; i++) {
            int xl = -(tower_width+1)/2;
            int xr = -xl;

            terrain.insert(Rocks::Coord(xl, i));
            terrain.insert(Rocks::Coord(xr, i));
        }
        num_walls += 10;

        // Spawn a new rock at the center of the tower
        Rocks::Rock rock = this->m_ROCKS[current_rock];

        // Set spawn position of rock 3 units above the previous rock
        bool collision = rock.translate(0, max_height+4, terrain);

        // Keep iterating until we collide with another rock in our terrain
        while (!collision) {
            int jet_direction = this->m_jetstream[current_jet] == '<' ? -1 : 1;
            current_jet = (current_jet + 1) % (this->m_jetstream.size());

            rock.translate(jet_direction, 0, terrain);
            collision = rock.translate(0, -1, terrain);
        }
        
        // We reach a collision, the rock becomes a part of the terrain
        for (const auto& coord : rock) {
            terrain.insert(coord);
            max_height = std::max(max_height, coord.second);

            int idx = coord.first+((tower_width-1)/2);
            current_surface[idx] = std::max(current_surface[idx], coord.second);
        }

        // Switch to the next rock
        current_rock = (RockType)(((int)(current_rock) + 1) % 5);
        num_rocks--;
    }
    
    return max_height + rep_height;
}

std::string Solution::hash_state(
    const RockType& rocktype, 
    const std::vector<long long>& surface, 
    const long long& jet_index,
    const long long& max_height
) const
{
    std::stringstream key;
    key << (int)(rocktype) << '-' << jet_index << '-';

    for (const long long& y : surface) {
        key << max_height - y << '-';
    }

    return key.str();
}
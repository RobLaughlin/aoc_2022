#include "Solution.h"
#include <fstream>
#include <regex>
#include <iostream>
#include <limits>
#include <stack>
#include <unordered_map>

using namespace Solution14;

const std::string Solution::INPUT_FILENAME = "input.txt";

Solution::Solution() {
    std::ifstream input (INPUT_FILENAME);

    std::string line;
    while (std::getline(input, line)) {
        parse_line(line);
    }
}

void Solution::parse_line(std::string line) {
    std::smatch x;
    std::smatch y;

    std::vector<HPair::IIPair> rocks;
    while (true) {
        std::regex_search(line, x, std::regex("\\d+"));
        if (x.empty()) { break; }
        int xc = std::stoi(x.str());
        line = x.suffix().str();

        std::regex_search(line, y, std::regex("\\d+"));
        int yc = std::stoi(y.str());
        line = y.suffix().str();
        
        HPair::IIPair coord = HPair::IIPair(xc, yc);
        rocks.push_back(coord);
    }

    if (!rocks.empty()) {
        this->coord_map[rocks[0]] = '#';
    }

    for (int i = 0; i < rocks.size()-1; i++) {
        const HPair::IIPair& from = rocks[i];
        const HPair::IIPair& to = rocks[i+1];

        // Create a copy to the from rock so we can iterate and add these to our coord map
        HPair::IIPair rock = from;
        int& to_inc = from.first == to.first ? rock.second : rock.first;
        int start;
        int stop;
        int inc;

        if (from.first == to.first) {
            start = from.second;
            stop = to.second;
            inc = to.second > from.second ? 1 : -1;
        }
        else if (from.second == to.second) {
            start = from.first;
            stop = to.first;
            inc = to.first > from.first ? 1 : -1;
        }

        for (int j = start; j != stop; j += inc) {
            to_inc += inc;
            this->coord_map[rock] = '#';
        }
    }
}

int Solution::find_sand_limit(int sand_source_x, int sand_source_y) {
    int sand_floor = std::numeric_limits<int>::min();
    
    // Find bottom of the sand floor (max row)
    for (auto const& kv : this->coord_map) {
        const HPair::IIPair& coord = kv.first;
        const int& row = coord.second;

        sand_floor = row > sand_floor ? row : sand_floor;
    }

    // Simulate sand falling
    HPair::IIPair sand_coord(sand_source_x, sand_source_y);
    int fallen = 0;
    while (true) {
        int& x = sand_coord.first;
        int& y = sand_coord.second;

        // Either we're backed up or falling into the void
        if (y < sand_source_y || y > sand_floor) {
            return fallen;
        }

        // Go straight down until blocked
        if (this->coord_map.find(HPair::IIPair(x, y+1)) == coord_map.end()) { y++; }

        // Go bottom-left if possible
        else if (this->coord_map.find(HPair::IIPair(x-1, y+1)) == coord_map.end()) { x--; y++; }

        // Go bottom-right if possible
        else if (this->coord_map.find(HPair::IIPair(x+1, y+1)) == coord_map.end()) { x++; y++; }

        // We've stopped!
        else {
            this->coord_map[sand_coord] = 'o';
            fallen++;

            sand_coord.first = sand_source_x;
            sand_coord.second = sand_source_y;
        }
    }
}
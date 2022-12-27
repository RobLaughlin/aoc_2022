#include "Solution.h"
#include <fstream>
#include <regex>
#include <limits>
#include <math.h>
#include "UnionFind.h"

using namespace Solution18;

const std::string Solution::INPUT_FILENAME = "input.txt";

Solution::Solution() : 
    x_bounds(std::pair<int, int>(std::numeric_limits<int>::max(), std::numeric_limits<int>::min())),
    y_bounds(std::pair<int, int>(std::numeric_limits<int>::max(), std::numeric_limits<int>::min())),
    z_bounds(std::pair<int, int>(std::numeric_limits<int>::max(), std::numeric_limits<int>::min()))
{
    std::ifstream input(INPUT_FILENAME);

    std::string line;
    while (std::getline(input, line)) {
        std::smatch match;

        int xyz[3] = {0, 0, 0};
        for (int i = 0; i < 3; i++) {
            std::regex_search(line, match, std::regex("-?\\d+"));
            xyz[i] = std::stoi(match.str());
            line = match.suffix().str();
        }

        Cube cube = Cube(xyz[0], xyz[1], xyz[2]);
        this->cubes[cube] = std::unordered_set<Cube>();
    }
    
    for (const auto& kv : this->cubes) {
        const Cube& cube = kv.first;

        std::vector<Cube> neighbors = get_neighbors(cube);
        for (const Cube& neighbor : neighbors) {
            if (this->cubes.find(neighbor) != this->cubes.end()) {
                this->cubes[cube].insert(neighbor);
            }
        }

        this->x_bounds.first = std::min(this->x_bounds.first, std::get<0>(cube));
        this->y_bounds.first = std::min(this->y_bounds.first, std::get<1>(cube));
        this->z_bounds.first = std::min(this->z_bounds.first, std::get<2>(cube));
        this->x_bounds.second = std::max(this->x_bounds.second, std::get<0>(cube));
        this->y_bounds.second = std::max(this->y_bounds.second, std::get<1>(cube));
        this->z_bounds.second = std::max(this->z_bounds.second, std::get<2>(cube));
    }
}

int Solution::surface_area(bool include_air_pockets) const {
    int sa = 0;

    for (const auto& kv : this->cubes) {
        const std::unordered_set<Cube>& connected = kv.second;
        const Cube& cube = kv.first;

        sa += 6 - connected.size();
    }

    if (include_air_pockets) {
        return sa;
    }

    UnionFind<Cube> airs;
    std::unordered_set<Cube> air_cubes;

    // Iterate over the entire space and connect all the 'air' cubes
    for (int x = this->x_bounds.first-1; x <= this->x_bounds.second+1; x++) {
        for (int y = this->y_bounds.first-1; y <= this->y_bounds.second+1; y++) {
            for (int z = this->z_bounds.first-1; z <= this->z_bounds.second+1; z++) {
                Cube c(x, y, z);

                // First, check if this cube is not a solid cube
                if (this->cubes.find(c) == this->cubes.end()) {

                    // If this cube is an air cube, connect it with other air cube neighbors
                    for (const Cube& neighbor : get_neighbors(c)) {
                        if (this->cubes.find(neighbor) == this->cubes.end()) {
                            airs.Union(c, neighbor);
                        }
                    }
                    air_cubes.insert(c);
                }
            }
        }
    }

    // This will be the cube we know for a fact isn't trapped
    Cube untrapped(this->x_bounds.first-1, this->y_bounds.first, this->z_bounds.first);

    /*
        For each air cube, check if we can connect to an untrapped cube.
        If we can't, then the air cube is trapped.

        For each trapped air cube, check if it's connected to a solid. 
        If it is, we remove the overlapping surface area.
    */
    for (const Cube& ac : air_cubes) {
        // If the air cube is not trapped, we don't care about it
        if (airs.connected(ac, untrapped)) { continue; }

        // If it is trapped, remove overlap with solids
        for (const Cube& neighbor : this->get_neighbors(ac)) {
            if (this->cubes.find(neighbor) != this->cubes.end()) {
                sa--;
            }
        }
    }

    return sa;
}

std::vector<Solution::Cube> Solution::get_neighbors(const Cube& cube) {
    using std::get;

    std::vector<Cube> neighbors;
    neighbors.push_back(Cube(get<0>(cube)+1, get<1>(cube), get<2>(cube)));
    neighbors.push_back(Cube(get<0>(cube)-1, get<1>(cube), get<2>(cube)));
    neighbors.push_back(Cube(get<0>(cube), get<1>(cube)+1, get<2>(cube)));
    neighbors.push_back(Cube(get<0>(cube), get<1>(cube)-1, get<2>(cube)));
    neighbors.push_back(Cube(get<0>(cube), get<1>(cube), get<2>(cube)+1));
    neighbors.push_back(Cube(get<0>(cube), get<1>(cube), get<2>(cube)-1));

    return neighbors;
}

bool Solution::is_air_pocket(const Cube& cube) const {
    // To find if this cube is an air pocket, 
    // it must be trapped between a cube in every adjacent direction.

    if (this->cubes.find(cube) != this->cubes.end()) {
        return false;
    }

    const int& x = std::get<0>(cube);
    const int& y = std::get<1>(cube);
    const int& z = std::get<2>(cube);

    // If we never encounter a cube, then its not trapped.
    bool trapped = false;

    for (int xp = this->x_bounds.first; xp <= this->x_bounds.second; xp++) {
        Cube c(xp, y, z);
        if (xp != x && this->cubes.find(c) != this->cubes.end()) {
            trapped = true;
            break;
        }
    }
    if (!trapped) { return false; }

    trapped = false;
    for (int yp = this->y_bounds.first; yp <= this->y_bounds.second; yp++) {
        Cube c(x, yp, z);
        if (yp != y && this->cubes.find(c) != this->cubes.end()) {
            trapped = true;
            break;
        }
    }
    if (!trapped) { return false; }

    trapped = false;
    for (int zp = this->z_bounds.first; zp <= this->z_bounds.second; zp++) {
        Cube c(x, y, zp);
        if (zp != z && this->cubes.find(c) != this->cubes.end()) {
            trapped = true;
            break;
        }
    }
    if (!trapped) { return false; }

    return true;
}
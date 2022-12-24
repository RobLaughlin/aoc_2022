#include "Rock.h"
#include <iostream>
#include <limits>

using namespace Rocks;

Rock::Rock() : CoordSet() {}

bool Rock::translate(long long x, long long y, const CoordSet& terrain) {
    Rock translated;

    for (auto it = this->begin(); it != this->end(); it++) {
        const long long xp = it->first + x;
        const long long yp = it->second + y;

        Coord coord(xp, yp);
        
        if (terrain.find(coord) != terrain.end()) {
            return true;
        }

        translated.insert(coord);
    }

    this->swap(translated);

    return false;
}

bool Rock::check_collision(const CoordSet& terrain) {
    for (auto it = this->begin(); it != this->end(); it++) {
        const Coord& coord = *it;

        if (terrain.find(coord) != terrain.end()) {
            return true; // Collision occured!
        }
    }

    return false;
}


Bar::Bar() : Rock()
{
    for (int x = -1; x < 3; x++) {
        this->insert(Coord(x,0));
    }
}

Cross::Cross() : Rock()
{
    this->insert(Coord(0, 0));
    this->insert(Coord(-1, 1));
    this->insert(Coord(0, 1));
    this->insert(Coord(1, 1));
    this->insert(Coord(0, 2));
}

L::L() : Rock() {
    this->insert(Coord(0, 0));
    this->insert(Coord(-1, 0));
    this->insert(Coord(1, 0));
    this->insert(Coord(1, 1));
    this->insert(Coord(1, 2));
}

Line::Line() : Rock() {
    for (int y = 0; y < 4; y++) {
        this->insert(Coord(-1, y));
    }
}

Square::Square() : Rock() {
    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 2; y++) {
            this->insert(Coord(x-1, y));
        }
    }
}
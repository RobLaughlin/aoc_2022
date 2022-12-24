#pragma once
#include <unordered_set>
#include "HPair.h"

namespace Rocks {
    typedef HPair::LLPair Coord;
    typedef std::unordered_set<Coord> CoordSet;
    
    struct Rock : CoordSet 
    {
        Rock();
        
        /*
            Translate a rock coordinates from (r,c) to (r+row, c+col).
            Clamps r+row and c+col between -clamp and clamp.
            Setting clamp to 0 yields the same result by not clamping at all. 
        */
        bool translate(long long x, long long y, const CoordSet& terrain);
        bool check_collision(const CoordSet& terrain); // Return true if a collision occured when translating
    };

    struct Bar : Rock { Bar(); };
    struct Cross : Rock { Cross(); };
    struct L : Rock { L(); };
    struct Line : Rock { Line(); };
    struct Square : Rock { Square(); };
};
#pragma once
#include <string>
#include <utility>
#include <vector>
#include "Grid.h"

namespace Solution24 {
    class Solution {
    public:
        typedef long long llong;
        typedef std::pair<int, int> Coord;
        typedef Grid<llong> State;

        // (state, coord of where E is located, minutes spent)
        typedef std::tuple<State, Coord, int> WrappedState;

        static const std::string INPUT_FILENAME;
        Solution();

        int fewest_minutes(Coord start, Coord finish);
        std::pair<Coord, Coord> get_endpoints() const;
    private:
        /*
            Each element of the grid will store particular integers corresponding 
            to what blizzards are active on that tile.

            Each element will correspond to the table below, where p is represented
            as an integer in base b, where b is the (width*height) of the grid.

            Suppose there are 5 rows and 5 columns for a given grid.
            Then p = c1*25^3 + c2*25^2 + c3*25 + c4.

            c1 is how many WEST (<) blizzards on that tile,
            c2 is how many SOUTH (v) blizzards, c3 is how many EAST (>) blizzards,
            and finally c4 is how many NORTH (^) blizzards there are on that tile.

            We can recover how many of each blizzard by taking mod 25 and subtracting the remainder.
            We know we'll recover the correct number of each blizzard because c1, c2, c3 and c4 are
            all less than 25.

            -2      -> E is on that tile.
            -1      -> tile is a wall (#).
             0      -> tile is empty
             p > 0  -> p = c1(rows*cols)^3 + c2(rows*cols)^2 + c3(rows*cols) + c4
        */
        State m_state;

        std::vector<WrappedState> get_neighbors(const WrappedState& wstate) const;
        std::string hash_state(const State& state) const; // Lazy hash to string
    };
};
#pragma once
#include "CubeFace.hpp"
#include <string>
#include <utility>
#include <vector>
#include <array>

namespace Solution22 {
    class Solution {
    public:
        // We're just gonna hardcode in our inputs to make things easy.
        enum Input {SAMPLE_INPUT, AOC_INPUT};
        enum Direction { RIGHT, DOWN, LEFT, UP };

        typedef std::pair<char, int> Move;

        struct State {
            int row;
            int col;
            Direction direction;
            const Face* face;
        };

        Solution(Input input_type);
        long long find_password(bool cube) const;
    private:
        Input m_input;
        Grid<char> m_grid;
        std::vector<Move> m_moves;
        std::array<Face, 6> m_faces;
        std::array<Face, 6> m_cube_faces;
        
        State next_state(const State& prev_state, const Move& move, bool cube) const;
    };
};
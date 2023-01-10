#include "Solution.hpp"
#include <fstream>
#include <unordered_map>
#include <limits>
#include <math.h>

#include <iostream>
using namespace Solution23;

const std::string Solution::INPUT_FILENAME = "input.txt";

Solution::Solution() {
    std::ifstream input(INPUT_FILENAME);

    std::string line;
    int row = 0;
    while (std::getline(input, line)) {
        for (int col = 0; col < line.length(); col++) {
            if (line[col] == '#') {
                this->elves.insert(Elf(row, col));
            }   
        }
        row++;
    }
}

int Solution::bounding_box_size(long long rounds) const {
    enum Direction {NORTH, SOUTH, WEST, EAST};
    Direction direction = NORTH;
    std::unordered_set<Elf, boost::hash<Elf>> elves_cpy = elves;

    for (int r = 0; r < rounds; r++) {
        std::unordered_map<Elf, Elf, boost::hash<Elf>> proposals;
        
        for (Elf elf : elves_cpy) {
            const int& row = std::get<0>(elf);
            const int& col = std::get<1>(elf);

            Elf N = Elf(row-1, col);
            Elf NW = Elf(row-1, col-1);
            Elf NE = Elf(row-1, col+1);
            Elf S = Elf(row+1, col);
            Elf SW = Elf(row+1, col-1);
            Elf SE = Elf(row+1, col+1);
            Elf W = Elf(row, col-1);
            Elf E = Elf(row, col+1);

            proposals[elf] = elf;

            if (elves_cpy.find(N) == elves_cpy.end()
                && elves_cpy.find(NW) == elves_cpy.end()
                && elves_cpy.find(NE) == elves_cpy.end()
                && elves_cpy.find(S) == elves_cpy.end()
                && elves_cpy.find(SW) == elves_cpy.end()
                && elves_cpy.find(SE) == elves_cpy.end()
                && elves_cpy.find(W) == elves_cpy.end()
                && elves_cpy.find(E) == elves_cpy.end()
            ) { continue; }

            int start = (int)(direction);
            for (int d = start; d < start+4; d++) {
                Direction cur_direction = (Direction)(d % 4);
                if (cur_direction == NORTH
                    && elves_cpy.find(N) == elves_cpy.end() 
                    && elves_cpy.find(NW) == elves_cpy.end()
                    && elves_cpy.find(NE) == elves_cpy.end()
                ) {
                    proposals[elf] = N; break;
                }
                else if (cur_direction == SOUTH
                    && elves_cpy.find(S) == elves_cpy.end() 
                    && elves_cpy.find(SE) == elves_cpy.end()
                    && elves_cpy.find(SW) == elves_cpy.end()
                ) {
                    proposals[elf] = S; break;
                }
                else if (cur_direction == WEST
                    && elves_cpy.find(W) == elves_cpy.end() 
                    && elves_cpy.find(NW) == elves_cpy.end()
                    && elves_cpy.find(SW) == elves_cpy.end()
                ) {
                    proposals[elf] = W; break;
                }
                else if (cur_direction == EAST
                    && elves_cpy.find(E) == elves_cpy.end() 
                    && elves_cpy.find(NE) == elves_cpy.end()
                    && elves_cpy.find(SE) == elves_cpy.end()
                ) {
                    proposals[elf] = E; break;
                }
            }
        }
        // std::cout << r << std::endl;

        std::unordered_map<Elf, int, boost::hash<Elf>> pos_counts;
        for (auto const& [elf, moved_elf] : proposals) {
            if (pos_counts.find(moved_elf) == pos_counts.end()) {
                pos_counts[moved_elf] = 0;
            }
            pos_counts[moved_elf]++;
        }

        std::unordered_set<Elf, boost::hash<Elf>> new_elves;
        for (auto const& [elf, moved_elf] : proposals) {
            if (pos_counts[moved_elf] == 1) {
                new_elves.insert(moved_elf);
            }
            else {
                new_elves.insert(elf);
            }
        }

        elves_cpy.swap(new_elves);
        direction = (Direction)(((int)(direction) + 1) % 4);
    }

    int min_row = std::numeric_limits<int>::max();
    int max_row = std::numeric_limits<int>::min();
    int min_col = std::numeric_limits<int>::max();
    int max_col = std::numeric_limits<int>::min();

    for (const Elf& elf : elves_cpy) {
        const int& row = std::get<0>(elf);
        const int& col = std::get<1>(elf);

        min_row = std::min(row, min_row);
        max_row = std::max(row, max_row);
        min_col = std::min(col, min_col);
        max_col = std::max(col, max_col);
    }

    return (max_col - min_col+1)*(max_row - min_row+1) - elves_cpy.size();
}

int Solution::find_first_round() const {
    enum Direction {NORTH, SOUTH, WEST, EAST};
    Direction direction = NORTH;
    std::unordered_set<Elf, boost::hash<Elf>> elves_cpy = elves;
    
    int round = 0;
    while (true) {
        std::unordered_map<Elf, Elf, boost::hash<Elf>> proposals;
        
        for (Elf elf : elves_cpy) {
            const int& row = std::get<0>(elf);
            const int& col = std::get<1>(elf);

            Elf N = Elf(row-1, col);
            Elf NW = Elf(row-1, col-1);
            Elf NE = Elf(row-1, col+1);
            Elf S = Elf(row+1, col);
            Elf SW = Elf(row+1, col-1);
            Elf SE = Elf(row+1, col+1);
            Elf W = Elf(row, col-1);
            Elf E = Elf(row, col+1);

            proposals[elf] = elf;

            if (elves_cpy.find(N) == elves_cpy.end()
                && elves_cpy.find(NW) == elves_cpy.end()
                && elves_cpy.find(NE) == elves_cpy.end()
                && elves_cpy.find(S) == elves_cpy.end()
                && elves_cpy.find(SW) == elves_cpy.end()
                && elves_cpy.find(SE) == elves_cpy.end()
                && elves_cpy.find(W) == elves_cpy.end()
                && elves_cpy.find(E) == elves_cpy.end()
            ) { continue; }

            int start = (int)(direction);
            for (int d = start; d < start+4; d++) {
                Direction cur_direction = (Direction)(d % 4);
                if (cur_direction == NORTH
                    && elves_cpy.find(N) == elves_cpy.end() 
                    && elves_cpy.find(NW) == elves_cpy.end()
                    && elves_cpy.find(NE) == elves_cpy.end()
                ) {
                    proposals[elf] = N; break;
                }
                else if (cur_direction == SOUTH
                    && elves_cpy.find(S) == elves_cpy.end() 
                    && elves_cpy.find(SE) == elves_cpy.end()
                    && elves_cpy.find(SW) == elves_cpy.end()
                ) {
                    proposals[elf] = S; break;
                }
                else if (cur_direction == WEST
                    && elves_cpy.find(W) == elves_cpy.end() 
                    && elves_cpy.find(NW) == elves_cpy.end()
                    && elves_cpy.find(SW) == elves_cpy.end()
                ) {
                    proposals[elf] = W; break;
                }
                else if (cur_direction == EAST
                    && elves_cpy.find(E) == elves_cpy.end() 
                    && elves_cpy.find(NE) == elves_cpy.end()
                    && elves_cpy.find(SE) == elves_cpy.end()
                ) {
                    proposals[elf] = E; break;
                }
            }
        }

        std::unordered_map<Elf, int, boost::hash<Elf>> pos_counts;
        for (auto const& [elf, moved_elf] : proposals) {
            if (pos_counts.find(moved_elf) == pos_counts.end()) {
                pos_counts[moved_elf] = 0;
            }
            pos_counts[moved_elf]++;
        }

        bool elf_moved = false;
        std::unordered_set<Elf, boost::hash<Elf>> new_elves;
        for (auto const& [elf, moved_elf] : proposals) {
            if (pos_counts[moved_elf] == 1) {
                new_elves.insert(moved_elf);
                if (moved_elf != elf) {
                    elf_moved = true;
                }   
            }
            else {
                new_elves.insert(elf);
            }
        }

        elves_cpy.swap(new_elves);
        direction = (Direction)(((int)(direction) + 1) % 4);
        round++;
        if (!elf_moved) {
            return round;
        }
    }

    return 0;
}
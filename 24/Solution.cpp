#include "Solution.hpp"
#include <fstream>
#include <math.h>
#include <queue>
#include <tuple>
#include <unordered_set>
#include <sstream>

using namespace Solution24;

const std::string Solution::INPUT_FILENAME = "input.txt";

Solution::Solution() {
    std::ifstream input(INPUT_FILENAME);

    // First determine the dimensions of the grid
    int rows = 0;
    int cols;

    std::string line;
    while (std::getline(input, line)) {
        rows++;
        cols = line.length();
    }
    input.clear();
    input.seekg(0);

    this->m_state = State(rows, cols, 0);

    int row = 0;
    llong grid_area = rows*cols;
    while (std::getline(input, line)) {
        for (int col = 0; col < line.length(); col++) {
            if (row == 0 && line[col] == '.') {
                this->m_state.place(-2, row, col);
            }
            else if (line[col] == '#') {
                this->m_state.place(-1, row, col);
            }
            else if (line[col] == '^') {
                this->m_state.place(1, row, col);
            }
            else if (line[col] == '>') {
                this->m_state.place(grid_area, row, col);
            }
            else if (line[col] == 'v') {
                this->m_state.place(std::pow(grid_area, 2), row, col);
            }
            else if (line[col] == '<') {
                this->m_state.place(std::pow(grid_area, 3), row, col);
            }
        }
        row++;
    }
}

int Solution::fewest_minutes(Coord start, Coord finish) {    
    // Every state is distance 1 (minute) away, 
    // so we can find the shortest path using BFS.
    // As soon as we find a state where we reach the end, we're done.
    WrappedState init_state(this->m_state, start, 0);
    std::queue<WrappedState> sq;
    sq.push(init_state);

    std::unordered_set<std::string> visited;

    while (!sq.empty()) {
        WrappedState sp = sq.front();
        sq.pop();

        const State& cur_state = std::get<0>(sp);
        const Coord& cur_pos = std::get<1>(sp);
        const int& minutes_spent = std::get<2>(sp);

        std::string sp_hash = this->hash_state(cur_state);
        if (visited.find(sp_hash) != visited.end()) { continue; }
        visited.insert(sp_hash);

        // Check if we've found our end state
        const int& cur_row = cur_pos.first;
        const int& cur_col = cur_pos.second;
        if (cur_pos == finish) {
            this->m_state = cur_state;
            // for (int row = 0; row < cur_state.get_rows(); row++) {
            //     for (int col = 0; col < cur_state.get_cols(); col++) {
            //         std::cout << "  " << cur_state.at(row, col) << "  ";
            //     }
            //     std::cout << std::endl;
            // }
            // std::cout << cur_state;
            return minutes_spent; 
        }

        // Otherwise, find all neighbor states and add them to the queue
        std::vector<WrappedState> neighbors = get_neighbors(sp);
        for (const WrappedState& neighbor : neighbors) {
            std::string nbr_hash = this->hash_state(std::get<0>(neighbor));
            if (visited.find(nbr_hash) == visited.end()) {
                sq.push(neighbor);
            }
        }
    }
    return -1;
}

std::pair<Solution::Coord, Solution::Coord> Solution::get_endpoints() const {
    std::pair<Coord, Coord> endpoints;
    for (int col = 0; col < this->m_state.get_cols(); col++) {
        if (this->m_state.at(0, col) == 0 || this->m_state.at(0, col) == -2) {
            endpoints.first = Coord(0, col);
        }
        if (this->m_state.at(this->m_state.get_rows()-1, col) == 0 || this->m_state.at(this->m_state.get_rows()-1, col) == -2) {
            endpoints.second = Coord(this->m_state.get_rows()-1, col);
        }
    }
    return endpoints;
}

std::vector<Solution::WrappedState> Solution::get_neighbors(const WrappedState& wstate) const {
    const State& state = std::get<0>(wstate);
    const Coord& pos = std::get<1>(wstate);
    const int& minutes_spent = std::get<2>(wstate);
    const llong grid_area = state.get_rows()*state.get_cols();
    
    std::vector<WrappedState> neighbors;

    // First, shift all the blizzards
    State shifted = State(state.get_rows(), state.get_cols(), 0);
    
    for (int row = 0; row < state.get_rows(); row++) {
        for (int col = 0; col < state.get_cols(); col++) {
            llong p = state.at(row, col);
            if (p == 0 || p == -2) { continue; }
            if (p == -1) { shifted.place(-1, row, col); continue; }

            // North, east, south, and west blizzards @ (row, col)
            llong blizzards[4] = {0,0,0,0};

            for (int i = 0; i < 4; i++) {
                blizzards[i] = p % grid_area;
                p -= blizzards[i];
                p = p / grid_area;
            }

            Coord north(row-1, col);
            Coord east(row, col+1);
            Coord south(row+1, col);
            Coord west(row, col-1);

            // Wrap around if we need to
            north.first = north.first <= 0 ? state.get_rows()-2 : north.first;
            east.second = east.second >= state.get_cols()-1 ? 1 : east.second;
            south.first = south.first >= state.get_rows()-1 ? 1 : south.first;
            west.second = west.second <= 0 ? state.get_cols()-2 : west.second;

            shifted.place(blizzards[0] + shifted.at(north.first, north.second), north.first, north.second);
            shifted.place(blizzards[1]*grid_area + shifted.at(east.first, east.second), east.first, east.second);
            shifted.place(blizzards[2]*std::pow(grid_area, 2) + shifted.at(south.first, south.second), south.first, south.second);
            shifted.place(blizzards[3]*std::pow(grid_area, 3) + shifted.at(west.first, west.second), west.first, west.second);
        }
    }

    const int& row = pos.first;
    const int& col = pos.second;

    // Next, find all states that we can move to
    Coord north(row-1, col);
    Coord east(row, col+1);
    Coord south(row+1, col);
    Coord west(row, col-1);

    std::vector<Coord> directions;
    directions.push_back(pos); // Add the direction where we don't move

    // Make sure we can't go out of bounds
    if (north.first > 0 || (north.first == 0 && shifted.at(north.first, north.second) == 0)) { directions.push_back(north); }
    if (east.second < state.get_cols()-1) { directions.push_back(east); }
    if (south.first < state.get_rows()-1 
        || (south.first == state.get_rows()-1 && shifted.at(south.first, south.second) == 0)) 
    { 
        directions.push_back(south); 
    }
    if (west.second > 0) { directions.push_back(west); }

    // Check if we can move in any of the cardinal directions,
    // and if we can, add that neighbor.
    for (const Coord& next_pos : directions) {

        // If there is no blizzard on this tile, add this possible neighbor state
        if (shifted.at(next_pos.first, next_pos.second) == 0) {
            State neighbor = shifted;
            neighbor.place(-2, next_pos.first, next_pos.second);
            neighbors.push_back(WrappedState(neighbor, next_pos, minutes_spent+1));
        }

    }

    return neighbors;
}

std::string Solution::hash_state(const Solution::State& state) const {
    std::stringstream hashed;

    for (int row = 0; row < state.get_rows(); row++) {
        for (int col = 0; col < state.get_cols(); col++) {
            hashed << state.at(row, col) << '-';
        }
    }

    return hashed.str();
}
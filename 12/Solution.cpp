#include "Solution.h"
#include <queue>
#include <limits>
#include <math.h>

const std::string Solution::INPUT_FILENAME = "input.txt";

Solution::Solution() {
    std::ifstream input(INPUT_FILENAME);

    std::string line;
    std::getline(input, line);
    int rows = 1;
    int cols = line.length();

    while (std::getline(input, line)) { rows++; }
    input.clear();
    input.seekg(0);

    this->heightmap = Grid<char>(rows, cols, '.');
    int row = 0;
    while (std::getline(input, line)) {
        for (int c = 0; c < line.length(); c++) {
            this->heightmap.place(line[c], row, c);
        }
        row++; 
    }

    input.close();
}

int Solution::shortest_path() const {
    // Lazy Dijkstra's Algorithm

    // pair (best distance to node, key from grid index)
    typedef std::pair<int, int> ppair;

    // Vector of visited nodes
    std::vector<bool> visited (this->heightmap.get_rows()*this->heightmap.get_cols(), false);

    // Maintain vector of best distances to each node from start
    std::vector<int> best_dist (visited.size(), std::numeric_limits<int>::max());

    // Min priority queue
    std::priority_queue<ppair, std::vector<ppair>, std::greater<ppair>> pq;

    // Find start and end nodes
    int start_idx = 0;
    int end_idx = 0;
    for (int r = 0; r < this->heightmap.get_rows(); r++) {
        for (int c = 0; c < this->heightmap.get_cols(); c++) {
            if (this->heightmap.at(r, c) == 'S') {
                start_idx = r*this->heightmap.get_cols()+c;
            }
            else if (this->heightmap.at(r, c) == 'E') {
                end_idx = r*this->heightmap.get_cols()+c;
            }
        }
    }

    pq.push(std::make_pair(0, start_idx));
    best_dist[start_idx] = 0;
    while (!pq.empty()) {
        ppair node = pq.top();
        pq.pop();

        const int& dist = node.first;
        const int& key = node.second;

        if (visited[key]) { continue; }
        visited[key] = true;

        const int row = floor(key / this->heightmap.get_cols());
        const int col = key % this->heightmap.get_cols();
        const char& node_val = this->heightmap.at(row, col);

        // Check if we hit the end
        if (node_val == 'E') {
            return best_dist[key];
        }

        // Right, left, top, and bottom neighbors respectively (if they exist)
        // Check if we have a shorter path to each neighbor node, and if we do, add it to the PQ
        const std::pair<int, int> neighbors[4] = {
            std::make_pair(row, col+1), 
            std::make_pair(row, col-1),
            std::make_pair(row-1, col),
            std::make_pair(row+1, col),
        };

        for (auto const& [n_row, n_col] : neighbors) {
            const int n_key =  n_row*this->heightmap.get_cols() + n_col;

            // If the neighbor is valid, we haven't visited it yet, and we've found a better path
            if (this->heightmap.in_bounds(n_row, n_col)) {
                char n_val = this->heightmap.at(n_row, n_col) == 'E' ? 'z' : this->heightmap.at(n_row, n_col);
                char val = node_val == 'S' ? 'a' : node_val;

                if (n_val <= val+1 && !visited[n_key] && dist + 1 < best_dist[n_key]) {
                    best_dist[n_key] = dist + 1;
                    pq.push(std::make_pair(dist + 1, n_key));
                }
            }
        }
    }

    return -1;
}
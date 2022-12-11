#include "Solution.h"

const std::string Solution::INPUT_FILENAME = "input.txt";

Solution::Solution()
{
    std::ifstream input(INPUT_FILENAME);

    std::string line;
    while (std::getline(input, line)) {
        char direction = line[0];
        int num_moves = std::stoi(line.substr(2));

        std::pair<char, int> move (direction, num_moves);
        this->moves.push_back(move);
    }
}

std::unordered_map<std::string, int>* Solution::get_tail_visits(int num_knots) const {
    std::vector<std::pair<int, int>> knots;
    std::unordered_map<std::string, int>* visited = new std::unordered_map<std::string, int>();

    std::string tail_key = pair_to_string<int>(std::pair<int, int>(0, 0));
    visited->insert({tail_key, 1});

    // Let the first element of the knot vector be the head of the chain.
    // The order of the vector is the order of the knots in the rope (or chain).
    for (int i = 0; i < num_knots; i++) {
        knots.push_back(std::pair<int, int>(0, 0));
    }

    for (const std::pair<char, int>& move : this->moves) {
        std::pair<int, int>* head_pos = &knots[0];

        for (int i = 0; i < move.second; i++) {
            switch (move.first) {
                case 'R': head_pos->second++; break;
                case 'U': head_pos->first--; break;
                case 'L': head_pos->second--; break;
                case 'D': head_pos->first++; break;
            }

            for (int j = 0; j < num_knots-1; j++) {
                head_pos = &knots[j];
                std::pair<int, int>* tail_pos = &(knots.at(j+1));

                if (pair_dist<int>(*head_pos, *tail_pos) >= 2) {
                    // Tail is not connected to head.
                    // We need to update the tail in this case.
        
                    update_tail(*head_pos, *tail_pos);

                    if (j+2 == num_knots) {
                        // Case where we're updating the end of the tail
                        tail_key = pair_to_string<int>(*tail_pos);
                        
                        if (visited->find(tail_key) == visited->end()) {
                            visited->insert({tail_key, 0});
                        }

                        (*visited)[tail_key]++;
                    }

                }
            }

            // Reset the head position back to the start
            head_pos = &knots[0];
        }

    }

    return visited;
}

int Solution::num_tail_visits(int num_knots) const {
    int visits = 0;
    std::unordered_map<std::string, int>* tail_visits = this->get_tail_visits(num_knots);
    
    for (auto const& kv : *tail_visits) {
        visits++;
    }

    delete tail_visits;
    return visits;
}

void Solution::update_tail(const std::pair<int, int>& head_pos, std::pair<int, int>& tail_pos) const {
    const int head_row = head_pos.first;
    const int head_col = head_pos.second;
    const int tail_row = tail_pos.first;
    const int tail_col = tail_pos.second;

    if (head_row == tail_row && head_col - tail_col == 2) {
        // Tail is 2 spaces to the left of head
        tail_pos.second++;
    }
    else if (head_row == tail_row && tail_col - head_col == 2) {
        // Tail is 2 spaces to the right of head
        tail_pos.second--;
    }
    else if (head_col == tail_col && head_row - tail_row == 2) {
        // Tail is 2 spaces above head
        tail_pos.first++;
    }
    else if (head_col == tail_col && tail_row - head_row == 2) {
        // Tail is 2 spaces below head
        tail_pos.first--;
    }
    else if (tail_row > head_row && tail_col < head_col) {
        // Tail is to the bottom-left of head
        tail_pos.first--;
        tail_pos.second++;
    }
    else if (tail_row > head_row && tail_col < head_col) {
        // Tail is to the bottom-left of head
        tail_pos.first--;
        tail_pos.second++;
    }
    else if (tail_row > head_row && tail_col > head_col) {
        // Tail is to the bottom-right of head
        tail_pos.first--;
        tail_pos.second--;
    }
    else if (tail_row < head_row && tail_col < head_col) {
        // Tail is to the top-left of head
        tail_pos.first++;
        tail_pos.second++;
    }
    else if (tail_row < head_row && tail_col > head_col) {
        // Tail is to the top-right of head
        tail_pos.first++;
        tail_pos.second--;
    }
}

template <typename T>
std::string Solution::pair_to_string(std::pair<T, T> pair) {
    std::stringstream sPair;
    sPair << '(' << pair.first << ',' << pair.second << ')';
    return sPair.str();
}

template <typename T>
double Solution::pair_dist(std::pair<T, T> pair1, std::pair<T, T> pair2) {
    double c1 = std::pow(pair1.first - pair2.first, 2);
    double c2 = std::pow(pair1.second - pair2.second, 2);

    return std::sqrt(c1 + c2);
}
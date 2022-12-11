#include "RopeSimulation.h"
#include <windows.h>
#include <unordered_set>

RopeSimulation::RopeSimulation(const std::string& input_file) {
    std::ifstream input(input_file);

    std::string line;
    while (std::getline(input, line)) {
        char direction = line[0];
        int num_moves = std::stoi(line.substr(2));

        std::pair<char, int> move (direction, num_moves);
        this->moves.push_back(move);
    }
}

std::vector<RopeSimulation::State>* RopeSimulation::run(int num_knots) const {
    if (num_knots < 1) { throw std::invalid_argument("Must have at least 1 knot(s) to simulate"); }

    std::vector<State>* states = new std::vector<State>();

    State state;
    for (int i = 0; i < num_knots; i++) {
        state.push_back(Knot(0, 0));
    }

    states->push_back(state);
    for (const std::pair<char, int>& move : this->moves) {
        Knot* head_pos = &state[0];

        for (int i = 0; i < move.second; i++) {
            switch (move.first) {
                case 'R': head_pos->second++; break;
                case 'U': head_pos->first--; break;
                case 'L': head_pos->second--; break;
                case 'D': head_pos->first++; break;
            }

            for (int j = 0; j < num_knots-1; j++) {
                head_pos = &state[j];
                std::pair<int, int>* tail_pos = &state[j+1];

                if (knot_dist(*head_pos, *tail_pos) >= 2) {
                    // Tail is not connected to head.
                    // We need to update the tail in this case.
                    update_tail(*head_pos, *tail_pos);
                }
            }

            // Reset the head position back to the start
            head_pos = &state[0];

            // State has changed, add state to state vector.
            states->push_back(state);
        }

    }
    return states;
}

void RopeSimulation::animate(int num_knots, std::ostream& out, int width, int height, int fps) const {
    std::vector<State>* states = this->run(num_knots);
    
    if (width % 2 == 0 || height % 2 == 0) {
        throw std::invalid_argument("Both width and height must be odd to always be centered around the head of the rope.");
    }

    if (width < 2*num_knots + 1 || height < 2*num_knots + 1) {
        throw std::invalid_argument("Width and height must be at least as big as 2*(number of knots)");
    }
    
    std::unordered_map<std::string, Knot> tail_visited;
    SimulationGrid clear(height, width, '\b');
    SimulationGrid grid(height, width, '.');
    const double wait_ms = 1000.0 / (double)fps;
    const int center_x = (width-1) / 2;
    const int center_y = (height-1) / 2;
    int shift_x = 0;
    int shift_y = 0;

    State* prev_state = &states->at(0);
    for (State& state : *states) {
        // Reset the grid back to dots
        for (int k = prev_state->size()-1; k >= 0; k--) {
            Knot knot = prev_state->at(k);
            grid.place('.', knot.first + center_y + shift_y, knot.second + center_x + shift_x);
        }

        // Remove the old visited tail markers
        for (auto const& [_, knot] : tail_visited) {
            grid.place('.', knot.first + center_y + shift_y, knot.second + center_x + shift_x);
        }

        // Recenter canvas if head is off screen
        const Knot& head = state[0];

        if (head.first > center_y) {
            shift_y = -(head.first - center_y);
        }
        else if (head.first < -center_y) {
            shift_y = -center_y - head.first;
        }

        if (head.second > center_x) {
            shift_x = -(head.second - center_x);
        }
        else if (head.second < -center_x) {
            shift_x = -center_x - head.second;
        }
        
        // Place the visited tail markers
        for (auto const& [_, knot] : tail_visited) {
            grid.place('#', knot.first + center_y + shift_y, knot.second + center_x + shift_x);
        }

        for (int k = state.size()-1; k >= 0; k--) {
            Knot knot = state.at(k);
            grid.place(char(k+'0'), knot.first + center_y + shift_y, knot.second + center_x + shift_x);
        }

        std::string tail_key = knot_to_string(state.back());
        if (tail_visited.find(tail_key) == tail_visited.end()) {
            tail_visited.insert({tail_key, state.back()});
        }

        prev_state = &state;
        
        Sleep(wait_ms);
        std::cout << clear << grid << std::endl;
    }

    delete states;
}
void RopeSimulation::save_sim(int num_knots, const std::string& output_filename) const {
    int min_width = 0;
    int max_width = 0;
    int min_height = 0;
    int max_height = 0;

    std::vector<State>* states = this->run(num_knots);
    std::unordered_set<std::string> tails;
    for (const State& state : *states) {
        const Knot& tail = state.back();
        min_height = tail.first < min_height ? tail.first : min_height;
        max_height = tail.first > max_height ? tail.first : max_height;
        min_width = tail.second < min_width ? tail.second : min_width;
        max_width = tail.second > max_width ? tail.second : max_width;

        const std::string tail_key = knot_to_string(tail);
        if (tails.find(tail_key) == tails.end()) {
            tails.insert(tail_key);
        }
    }

    int width = max_width - min_width;
    int height = max_height - min_height;
    
    // Force width and height to be odd to have a true "center" knot
    width += width % 2 ? 1 : 0;
    height += height % 2 ? 1 : 0;
    const int center_x = (width-1)/2;
    const int center_y = (height-1)/2;

    std::ofstream out(output_filename);
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            const Knot coord (r-center_y, c-center_x);
            const std::string coord_key = knot_to_string(coord);

            if (tails.find(coord_key) == tails.end()) {
                out << '.';
            }
            else {
                out << '#';
            }
        }
        out << std::endl;
    }
    out.close();
}

void RopeSimulation::update_tail(const RopeSimulation::Knot& head_pos, RopeSimulation::Knot& tail_pos) const {
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

std::string RopeSimulation::knot_to_string(RopeSimulation::Knot knot) {
    std::stringstream sKnot;
    sKnot << '(' << knot.first << ',' << knot.second << ')';
    return sKnot.str();
}

double RopeSimulation::knot_dist(Knot knot1, Knot knot2) {
    double c1 = std::pow(knot1.first - knot2.first, 2);
    double c2 = std::pow(knot1.second - knot2.second, 2);

    return std::sqrt(c1 + c2);
}
#include "Solution.h"
#include <fstream>
#include <regex>
#include <unordered_set>
#include <sstream>
#include <math.h>
#include <queue>
#include <stack>
#include <tuple>

#include <iostream>
using namespace Solution16;

const std::string Solution::INPUT_FILENAME = "input.txt";

Solution::Solution() 
    : valves(std::vector<Valve>()), shortest_path_matrix(std::vector<std::vector<int>>())
{
    std::ifstream input(INPUT_FILENAME);

    // Get the index of each valve and put them in a map so we can store them
    std::unordered_map<std::string, int> index_map;
    int i = 0;
    std::string line;
    while (std::getline(input, line)) {
        std::string ID = line.substr(6, 2);
        index_map[ID] = i;
        i++;
    }
    input.clear();
    input.seekg(0, std::ios::beg);

    while (std::getline(input, line)) {
        std::string ID = line.substr(6, 2); // Valve ID
        line = line.substr(9);

        std::smatch match;
        std::regex_search(line, match, std::regex("\\d+"));
        int flow_rate = std::stoi(match.str()); // Valve Flow Rate
        line = match.suffix().str();
        
        // Connected valves
        std::unordered_set<int> connected;
        connected.insert(index_map[ID]);
        while (std::regex_search(line, match, std::regex("[A-Z]{2}"))) {
            int i = index_map[match.str()];
            if (connected.find(i) == connected.end()) {
                connected.insert(i);
            }
            line = match.suffix().str();
        }

        this->valves.push_back(Valve(ID, flow_rate, connected));

    }

    this->populate_shortest_paths();
}

std::vector<Solution::Path> Solution::find_all_paths(int start_valve, int time_budget) const {
    // Return ALL paths with a fully spent time budget.
    // Use DFS to span all state paths.
    std::vector<Path> paths;
    std::unordered_set<std::string> visited;
    std::stack<State> statestack;

    State init_state(start_valve, time_budget, 0, 0);
    statestack.push(init_state);
    while (!statestack.empty()) {
        State current = statestack.top();
        statestack.pop();

        std::string current_hash = state_hash(current);
        if (visited.find(current_hash) != visited.end()) {
            continue; // Already examined this state, move on.
        }
        visited.insert(current_hash);

        const int& valve = std::get<0>(current);
        const int& time_remaining = std::get<1>(current);
        const long long& opened_state = std::get<2>(current);
        const long long& pressure = std::get<3>(current);
        const long long new_pressure = pressure + (time_remaining-1)*this->valves[valve].flow_rate;

        // Found a new path!
        // Only add this path if we've maxed out our time budget
        if (time_remaining == 0) {
            Path p;
            std::stack<State> statestack_cpy = statestack;
            p.push_back(current);
            while (!statestack_cpy.empty()) {
                p.push_back(statestack_cpy.top());
                statestack_cpy.pop();
            }
            std::reverse(p.begin(), p.end());
            paths.push_back(p);
        }


        // Now there are 2 cases for how we can branch our state
        // (1) We can move to another valve without opening.
        // (2) We can open a valve
        const bool valve_open = ((long long)1 << valve) & opened_state;
        for (int i = 0; i < this->valves.size(); i++) {
            const int& dist = this->shortest_path_matrix[valve][i];
            
            // Case (1)
            if (time_remaining-dist >= 0 && this->valves[i].flow_rate != 0) {
                statestack.push(State(i, time_remaining-dist, opened_state, pressure));
            }
        }

        // Case (2)
        if (!valve_open && time_remaining-1 >= 0 && this->valves[valve].flow_rate != 0) {
            statestack.push(State(valve, time_remaining-1, ((long long)1 << valve) | opened_state, new_pressure));
        }
    }

    // Trim ALL nodes with suboptimal pressures
    std::vector<Path> trimmed_paths;
    typedef std::unordered_map<long long, Path> OrderingSet;

    OrderingSet orderings;
    for (const Path& path : paths) {
        const long long& opening_state = std::get<2>(path.back());
        const long long& pressure = std::get<3>(path.back());

        if (orderings.find(opening_state) == orderings.end()) {
            orderings[opening_state] = path;
        }

        const long long& prev_pressure = std::get<3>(orderings[opening_state].back());
        if (pressure > prev_pressure) {
            orderings[opening_state] = path;
        }
    }

    for (auto const& kv : orderings) {
        trimmed_paths.push_back(kv.second);
    }

    // We'll sort our trimmed paths by maximum pressure too.
    auto sort_key = [](const Path& p1, const Path& p2) {
        const long long pressure1 = std::get<3>(p1[p1.size()-1]);
        const long long pressure2 = std::get<3>(p2[p2.size()-1]);

        return pressure1 > pressure2;
    };
    std::sort(trimmed_paths.begin(), trimmed_paths.end(), sort_key);

    return trimmed_paths;
}

long long Solution::max_pressure(int start_valve, int time_budget, bool with_elephant) const {
    std::vector<Path> paths = find_all_paths(start_valve, time_budget);

    if (!with_elephant) {
        return std::get<3>(paths.front().back());
    }

    long long best_pressure = 0;
    for (int i = 0; i < paths.size(); i++) {
        const Path& l_path = paths[i];
        const long long& l_pressure = std::get<3>(l_path.back());
        const long long& l_state = std::get<2>(l_path.back());

        for (int j = 0; j < paths.size(); j++) {
            const Path& r_path = paths[j];
            const long long& r_pressure = std::get<3>(r_path.back());
            const long long& r_state = std::get<2>(r_path.back());
            
            // Paths must be disjoint!
            if ((r_state & l_state) == 0) {
                best_pressure = std::max(best_pressure, l_pressure + r_pressure);
            }
        }
    }

    return best_pressure;
}

void Solution::populate_shortest_paths() {
    // Run BFS on each node pair to populate the shortest path pair matrix.
    for (int r = 0; r < this->valves.size(); r++) {
        this->shortest_path_matrix.push_back(std::vector<int>());

        for (int c = 0; c < this->valves.size(); c++) {
            std::queue<std::pair<int, int>> q;
            q.push(std::make_pair(r, 0));

            while (!q.empty()) {
                int i = q.front().first;
                int dist = q.front().second;

                q.pop();

                if (i == c) {
                    this->shortest_path_matrix[r].push_back(dist);
                    break;
                }

                for (const int neighbor : this->valves[i].connected) {
                    q.push(std::make_pair(neighbor, dist+1));
                }
            }
        }
    }

    // Distance to move to self node is still 1
    for (int r = 0; r < this->valves.size(); r++) {
        this->shortest_path_matrix[r][r] = 1;
    }
}

std::string Solution::state_hash(const State& state) {
    std::stringstream key;
    key << std::get<0>(state) << '-' << std::get<1>(state) << '-' << std::get<2>(state) << '-' << std::get<3>(state);
    return key.str();
}

#include "Solution.hpp"
#include <fstream>
#include <regex>
#include <math.h>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include "GameState.hpp"

#include <iostream>
using namespace Solution19;

const std::string Solution::INPUT_FILENAME = "input.txt";

Solution::Solution() 
    : blueprints(std::vector<Blueprint>())
{
    std::ifstream input(INPUT_FILENAME);

    std::string line;
    while (std::getline(input, line)) {
        std::smatch match;

        std::regex_search(line, match, std::regex("\\d+"));
        line = match.suffix().str();

        long long costs[6] = {0,0,0,0,0,0};
        for (long long& cost : costs) {
            std::regex_search(line, match, std::regex("\\d+"));
            cost += std::stoi(match.str());
            line = match.suffix().str();
        }

        Blueprint blueprint(costs[0], costs[1], std::make_pair(costs[2], costs[3]), std::make_pair(costs[4], costs[5]));
        this->blueprints.push_back(blueprint);
    }
}

long long Solution::quality_sum(long long time_remaining) const {
    long long qs = 0;
    for (int i = 0; i < this->blueprints.size(); i++) {
        qs += (i+1)*find_max_geodes(i, time_remaining);
    }
    return qs;
}

long long Solution::geode_multiplier(long long time_remaining) const {
    long long m = 1;
    for (int i = 0; i < std::min((int)this->blueprints.size(), 3); i++) {
        m *= find_max_geodes(i, time_remaining);
    }
    return m;
}
long long Solution::find_max_geodes(int blueprint_id, long long time_remaining) const {

    if (blueprint_id < 0 || blueprint_id >= this->blueprints.size()) {
        throw std::invalid_argument("Invalid blueprint id");
    }

    const Blueprint& blueprint = this->blueprints[blueprint_id];
    long long max_geodes = 0;

    std::unordered_set<std::string> visited;
    std::queue<GameState> q;
    GameState init_state(blueprint, time_remaining);
    q.push(init_state);
    
    while (!q.empty()) {
        const GameState gs = q.front();
        const std::string gs_key = gs.to_string();
        q.pop();

        // Check if we've already visited this node
        if (visited.find(gs_key) != visited.end()) { continue; }

        max_geodes = std::max(max_geodes, gs.state[7]);
        visited.insert(gs_key);

        for (const GameState& neighbor : gs.find_neighbors()) {
            const std::string neighbor_key = neighbor.to_string();
            if (visited.find(neighbor_key) != visited.end()) { continue; }

            q.push(neighbor);
        }
    }
    return max_geodes;
}
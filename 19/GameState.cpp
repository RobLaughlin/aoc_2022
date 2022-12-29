#include "GameState.hpp"
#include <sstream>
#include <math.h>

GameState::GameState(const Blueprint blueprint, long long time_remaining) 
    : state(State({1,0,0,0,0,0,0,0,time_remaining})), BLUEPRINT(blueprint) 
{}

GameState::GameState(const State state, const Blueprint blueprint)
    : state(state), BLUEPRINT(blueprint) {}

std::vector<GameState> GameState::find_neighbors() const {
    std::vector<GameState> states;
    State s = this->state;

    long long& ore_robots       = s[0];
    long long& clay_robots      = s[1];
    long long& obsidian_robots  = s[2];
    long long& geode_robots     = s[3];
    long long& ore              = s[4];
    long long& clay             = s[5];
    long long& obsidian         = s[6];
    long long& geodes           = s[7];
    long long& time_remaining   = s[8];

    // If we have no time remaining, we have no neighbors
    if (time_remaining <= 0) { return states; }

    auto collect_resources = [](State s, int robot_created) {
        for (int i = 0; i < 4; i++) {
            s[i+4] += s[i] - (int)(i == robot_created);
        }
        return s;
    };

    int max_ore = std::max(BLUEPRINT.ore_cost, BLUEPRINT.clay_cost);
    max_ore = std::max(max_ore, BLUEPRINT.obsidian_cost.first);
    max_ore = std::max(max_ore, BLUEPRINT.geode_cost.first);
    int max_clay = BLUEPRINT.obsidian_cost.second;
    int max_obsidian = BLUEPRINT.geode_cost.second;

    // Throw away our extra resources
    ore = std::min(ore, (time_remaining)*max_ore);
    clay = std::min(clay, (time_remaining)*max_clay);
    obsidian = std::min(obsidian, (time_remaining)*max_obsidian);

    // Decrement the time
    time_remaining--;

    // Cases where we make a robot
    // Notice we don't need to make a robot if we have more robots than cost to make a robot.
    // We'll overflow with resources if we consider those cases.

    // Always prioritize making a geode robot if we can
    if (ore >= BLUEPRINT.geode_cost.first && obsidian >= BLUEPRINT.geode_cost.second) {
        ore -= BLUEPRINT.geode_cost.first;
        obsidian -= BLUEPRINT.geode_cost.second;
        geode_robots++;
        states.push_back(GameState(collect_resources(s, 3), BLUEPRINT));
        geode_robots--;
        ore += BLUEPRINT.geode_cost.first;
        obsidian += BLUEPRINT.geode_cost.second;

        return states; // Early return, why make any other robot here?
    }

    // We really only need to make robots if we need resources to make a geode robot.
    if (ore_robots >= BLUEPRINT.geode_cost.first && obsidian_robots >= BLUEPRINT.geode_cost.second) {
        return states;
    }

    if (ore >= BLUEPRINT.ore_cost && ore_robots <= max_ore) {
        ore -= BLUEPRINT.ore_cost;
        ore_robots++;
        states.push_back(GameState(collect_resources(s, 0), BLUEPRINT));
        ore_robots--;
        ore += BLUEPRINT.ore_cost;
    }

    if (ore >= BLUEPRINT.clay_cost && clay_robots <= BLUEPRINT.obsidian_cost.second) {
        ore -= BLUEPRINT.clay_cost;
        clay_robots++;
        states.push_back(GameState(collect_resources(s, 1), BLUEPRINT));
        clay_robots--;
        ore += BLUEPRINT.clay_cost;
    }

    if (ore >= BLUEPRINT.obsidian_cost.first && clay >= BLUEPRINT.obsidian_cost.second && obsidian_robots <= BLUEPRINT.geode_cost.second) {
        ore -= BLUEPRINT.obsidian_cost.first;
        clay -= BLUEPRINT.obsidian_cost.second;
        obsidian_robots++;
        states.push_back(GameState(collect_resources(s, 2), BLUEPRINT));
        obsidian_robots--;
        ore += BLUEPRINT.obsidian_cost.first;
        clay += BLUEPRINT.obsidian_cost.second;
    }
    
    // Only wait for materials when we might have to
    if (    (ore < BLUEPRINT.ore_cost && ore_robots > 0)
        ||  (ore < BLUEPRINT.clay_cost && ore_robots > 0)
        ||  (ore < BLUEPRINT.obsidian_cost.first && ore_robots > 0)
        ||  (clay < BLUEPRINT.obsidian_cost.second && clay_robots > 0)
        ||  (ore < BLUEPRINT.geode_cost.first && ore_robots > 0)
        ||  (obsidian < BLUEPRINT.geode_cost.second && obsidian_robots > 0)
    ) {
        
        states.push_back(GameState(collect_resources(s, -1), BLUEPRINT));
    }
    
    return states;
}

std::string GameState::to_string(bool with_geodes) const {
    std::stringstream key;
    for (int i = 0; i < this->state.size(); i++) {
        const long long& quantity = this->state[i];
        if (!with_geodes && i == 7) { continue; }

        key << quantity << '-';
    }
    return key.str();
}
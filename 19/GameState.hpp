#pragma once
#include <array>
#include <vector>
#include <string>
#include "Blueprint.hpp"

class GameState {
public:
    typedef std::array<long long, 9> State;

    GameState(const Blueprint blueprint, long long time_remaining);
    GameState(const State state, const Blueprint blueprint);

    std::vector<GameState> find_neighbors() const;
    std::string to_string(bool with_geodes=true) const;

    /*
        state[0] = number of ore robots
        state[1] = number of clay robots
        state[2] = number of obsidian robots
        state[3] = number of geode robots
        state[4] = amount of ore
        state[5] = amount of clay
        state[6] = amount of obsidian
        state[7] = amount of geodes
        state[8] = time remaining
    */
    State state;
    const Blueprint BLUEPRINT;
private:
    GameState();
};
#pragma once
#include "Valve.h"
#include <vector>
#include <unordered_map>

namespace Solution16 {
    class Solution {
    public:
        /*
            (current valve, time remaining, open states, pressure)
            The 3rd int (open states) is a bit mask. Ex: 1011 means valves 0, 2, and 3 are open and valve 1 is closed.
        */
        typedef std::tuple<int, int, long long, long long> State;
        typedef std::vector<State> Path;

        static const std::string INPUT_FILENAME;
        
        std::vector<Valve> valves;

        Solution();
        std::vector<Path> find_all_paths(int start_valve, int time_budget) const;
        long long max_pressure(int start_valve, int time_budget, bool with_elephant=false) const;
    private:
        std::vector<std::vector<int>> shortest_path_matrix;
        void populate_shortest_paths();
        static std::string state_hash(const State& state);
        static std::string path_hash(const Path& state);
    };
};

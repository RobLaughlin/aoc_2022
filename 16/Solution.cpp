#include "Solution.h"
#include <fstream>
#include <regex>
#include <unordered_set>
#include <sstream>

using namespace Solution16;

const std::string Solution::INPUT_FILENAME = "input.txt";

Solution::Solution() 
    : valves(std::vector<Valve>())
{
    std::ifstream input(INPUT_FILENAME);

    std::string line;

    // Get the index of each valve and put them in a map so we can store them
    std::unordered_map<std::string, int> index_map;
    int i = 0;
    while (std::getline(input, line)) {
        std::string ID = line.substr(6, 2);
        index_map[ID] = i;
        i++;
    }
    input.clear();
    input.seekg(0, std::ios::beg);

    while (std::getline(input, line)) {
        std::string ID = line.substr(6, 2);
        line = line.substr(9);

        std::smatch match;
        std::regex_search(line, match, std::regex("\\d+"));
        int flow_rate = std::stoi(match.str());
        line = match.suffix().str();

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
}

long long Solution::find_max_pressure(
    int valve_index,
    int time_bank,
    std::unordered_map<std::string, long long>& memo,
    std::unordered_set<int> opened
) const {
    if (valve_index < 0 || valve_index >= this->valves.size()) {
        throw std::invalid_argument("Invalid valve index.");
    }

    if (time_bank <= 0) { return 0; }
    
    std::string key = make_state_hash(valve_index, time_bank, opened);
    if (memo.find(key) != memo.end()) {
        return memo[key];
    }

    long long max_pressure = -1;
    for (const int& c : this->valves[valve_index].connected) {
        long long pressure = find_max_pressure(c, time_bank-1, memo, opened);
        if (pressure > max_pressure) {
            max_pressure = pressure;
        }
    }
    
    // Valve is closed. We can open it!
    if (opened.find(valve_index) == opened.end() && this->valves[valve_index].flow_rate != 0) {
        opened.insert(valve_index);

        long long released = (time_bank-1)*this->valves[valve_index].flow_rate;
        for (const int& c : this->valves[valve_index].connected) {
            long long pressure = released + find_max_pressure(c, time_bank-2, memo, opened);
            if (pressure > max_pressure) {
                max_pressure = pressure;
            }
        }
    }

    memo[key] = max_pressure;
    return max_pressure;
}

std::string Solution::make_state_hash(const int& current_valve, const int& time_bank, const std::unordered_set<int>& opened) const {
    std::stringstream key;
    key << current_valve << '-' << time_bank << '-';
    for (int i = 0; i < this->valves.size(); i++) {
        key << (int)(opened.find(i) != opened.end());
    }
    return key.str();
}
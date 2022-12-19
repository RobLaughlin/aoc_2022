#include "Solution.h"
#include <fstream>
#include <regex>
#include <algorithm>

#include <iostream>
using namespace Solution15;

const std::string Solution::INPUT_FILENAME = "input.txt";

Solution::Solution() 
    : sbpairs(std::vector<std::pair<Sensor, Beacon>>())
{
    std::ifstream input (INPUT_FILENAME);

    std::string line;
    while (std::getline(input, line)) {
        std::smatch match;
        std::pair<Sensor, Beacon> sbpair = std::make_pair(Sensor(), Beacon());

        int* ptrs[4] = {&sbpair.first.first, &sbpair.first.second, &sbpair.second.first, &sbpair.second.second};
        for (int* const p : ptrs) {
            std::regex_search(line, match, std::regex("-?\\d+"));
            *p = std::stoi(match.str());
            line = match.suffix().str();
        }
        this->sbpairs.push_back(sbpair);
    }
}

int Solution::positions_without_beacon(int row, int min_row, int max_row) const {
    int total = 0;

    // First, generate a vector of intervals to merge (for the given row)
    std::vector<std::pair<int, int>> intervals;

    for (const std::pair<Sensor, Beacon>& sbpair : this->sbpairs) {
        int sbdist = dist(sbpair.first, sbpair.second);
        int rowdist = abs(row - sbpair.first.second); // Distance between target row and y coord of our sensor

        // Check if we can even reach the given row with how big our scanner-beacon distance is
        if (rowdist > sbdist) { continue; }

        // If we can reach the target row, then we can create a valid interval out of it
        const int& sensor_x = sbpair.first.first;
        std::pair<int, int> interval (std::max(sensor_x - (sbdist-rowdist), min_row), std::min(sensor_x + (sbdist-rowdist), max_row));
        intervals.push_back(interval);
    }

    // Now to merge the intervals into multiple disjoint intervals, then add.
    merge_intervals(intervals);
    for (std::pair<int, int> interval : intervals) {
        total += (interval.second - interval.first);
    }
    return total;
}

size_t Solution::tuning_frequency(int min_row, int max_row) const {
    for (int i = min_row; i < max_row; i++) {
        int total = 0;

        // First, generate a vector of intervals to merge (for the given row)
        std::vector<std::pair<int, int>> intervals;

        for (const std::pair<Sensor, Beacon>& sbpair : this->sbpairs) {
            int sbdist = dist(sbpair.first, sbpair.second);
            int rowdist = abs(i - sbpair.first.second); // Distance between target row and y coord of our sensor

            // Check if we can even reach the given row with how big our scanner-beacon distance is
            if (rowdist > sbdist) { continue; }

            // If we can reach the target row, then we can create a valid interval out of it
            const int& sensor_x = sbpair.first.first;
            std::pair<int, int> interval (std::max(sensor_x - (sbdist-rowdist), min_row), std::min(sensor_x + (sbdist-rowdist), max_row));
            intervals.push_back(interval);
        }

        // Now to merge the intervals into multiple disjoint intervals.
        merge_intervals(intervals);

        // Now we check if there's a gap of 1
        for (std::pair<int, int> interval : intervals) {
            total += (interval.second - interval.first);
        }

        if (total == (max_row-min_row-2)) {
            if (intervals.size() == 2) {
                return (size_t)(intervals[0].second+1)*4000000+i;
            }

            if (intervals[0].second == max_row) {
                return (size_t)(min_row)*4000000+i;
            }

            return (size_t)(max_row)*4000000+i;
        }
    }
    return 0;
}

bool Solution::disjoint(const std::pair<int, int>& interval1, const std::pair<int, int>& interval2) {
    return std::max(interval1.first, interval2.first) > std::min(interval1.second, interval2.second);
}

void Solution::merge_intervals(std::vector<std::pair<int, int>>& intervals) const {
    if (intervals.size() <= 1) { return; }

    // Sort based on left-endpoints
    auto sort_key = [](const std::pair<int, int>& interval1, const std::pair<int, int>& interval2) {
        return interval1.first < interval2.first;
    };

    std::sort(intervals.begin(), intervals.end(), sort_key);
    std::vector<std::pair<int, int>> merged;
    merged.push_back(intervals[0]);

    for (int i = 1; i < intervals.size(); i++) {
        if (disjoint(merged.back(), intervals[i])) {
            merged.push_back(intervals[i]);
        } 
        else {
            merged.back().second = std::max(merged.back().second, intervals[i].second);
        }
    }

    intervals = merged;
}

int Solution::dist(const Sensor& sensor, const Beacon& beacon) {
    return abs(sensor.first - beacon.first) + abs(sensor.second - beacon.second);
}
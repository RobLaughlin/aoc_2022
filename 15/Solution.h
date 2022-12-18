#pragma once
#include <string>
#include <utility>
#include <vector>

namespace Solution15 {
    class Solution {
    public:
        typedef std::pair<int, int> Sensor;
        typedef std::pair<int, int> Beacon;

        static const std::string INPUT_FILENAME;
        Solution();

        int positions_without_beacon(int row);
        bool disjoint(const std::pair<int, int>& interval1, const std::pair<int, int>& interval2);
        void merge_intervals(std::vector<std::pair<int, int>>& intervals);
    private:
        std::vector<std::pair<Sensor, Beacon>> sbpairs;

        // Calculate taxicab distance between sensor and beacon
        static int dist(const Sensor& sensor, const Beacon& beacon);
    };
};
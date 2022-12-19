#pragma once
#include <string>
#include <utility>
#include <vector>
#include <limits>

namespace Solution15 {
    class Solution {
    public:
        typedef std::pair<int, int> Sensor;
        typedef std::pair<int, int> Beacon;

        static const std::string INPUT_FILENAME;
        Solution();

        int positions_without_beacon(int row, int min_row=std::numeric_limits<int>::min(), int max_row=std::numeric_limits<int>::max()) const;
        size_t tuning_frequency(int min_row, int max_row) const;
        
        void merge_intervals(std::vector<std::pair<int, int>>& intervals) const;
    private:
        std::vector<std::pair<Sensor, Beacon>> sbpairs;

        static bool disjoint(const std::pair<int, int>& interval1, const std::pair<int, int>& interval2);

        // Calculate taxicab distance between sensor and beacon
        static int dist(const Sensor& sensor, const Beacon& beacon);
    };
};
#include "Solution.hpp"
#include <fstream>
#include <unordered_map>
#include <math.h>
#include "HashableTuple.hpp"

using namespace Solution20;

const std::string Solution::INPUT_FILENAME = "input.txt";

Solution::Solution() {
    std::ifstream input(INPUT_FILENAME);

    std::string line;
    while (std::getline(input, line)) {
        this->m_nums.push_back(std::stoi(line));
    }
}

Solution::llong Solution::grove_coord_sum(llong num_mixes, llong decryption_key) const {
    llong gcs = 0;
    std::vector<llong> mixed = mix_nums(num_mixes, decryption_key);
    for (llong i = 0; i < mixed.size(); i++) {
        if (mixed[i] == 0) {
            llong gc1 = mixed[(i + 1000) % mixed.size()];
            llong gc2 = mixed[(i + 2000) % mixed.size()];
            llong gc3 = mixed[(i + 3000) % mixed.size()];
            gcs = gc1 + gc2 + gc3;
            return gcs;
        }
    }

    return 0;
}

std::vector<Solution::llong> Solution::mix_nums(llong num_mixes, llong decryption_key) const {
    // Make every integer in our nums vector unique.
    // IDInt is the pair (num, num_id)
    typedef HTuple<llong, llong> IDInt;

    std::unordered_map<IDInt, llong> index_map;
    std::vector<IDInt> swapped_nums;

    // Fill in the index map
    for (llong i = 0; i < this->m_nums.size(); i++) {
        IDInt id_int = IDInt(this->m_nums[i]*decryption_key, i);
        index_map[id_int] = i;
        swapped_nums.push_back(id_int);
    }

    for (llong n = 0; n < num_mixes; n++) {
        for (llong i = 0; i < swapped_nums.size(); i++) {
            const llong num = this->m_nums[i]*decryption_key;
            const llong start = index_map[IDInt(num, i)];
            const llong sign = this->m_nums[i] >= 0 ? 1 : -1;

            // Always need a positive index
            llong end = start;
            end += sign*(std::abs(num) % (this->m_nums.size()-1));
            end = end <= 0 ? end+this->m_nums.size()-1 : end;
            end = end >= this->m_nums.size() ? (end % m_nums.size())+1: end;

            const llong dir = end >= start ? 1 : -1;
            for (llong j = start; j != end; j += dir) {
                // Swap j and j+dir
                const IDInt cur_elem = swapped_nums[j];
                const IDInt next_elem = swapped_nums[j + dir];

                index_map[cur_elem] = j + dir;
                index_map[next_elem] = j;
                swapped_nums[j] = next_elem;
                swapped_nums[j + dir] = cur_elem;
            }
        }
    }

    std::vector<llong> nums;
    for (const IDInt& id_int : swapped_nums) {
        nums.push_back(std::get<0>(id_int));
    }

    return nums;
}
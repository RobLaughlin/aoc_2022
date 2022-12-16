#include "Solution.h"

int main() {
    Solution sol;
    std::cout << "Sum of indices of pairs with packets in the right order: " << sol.count_indices() << std::endl;
    std::cout << "Decoder key: " << sol.find_decoder_key() << std::endl;
    return 0;
}
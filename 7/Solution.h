#pragma once
#include <fstream>
#include <regex>
#include <limits>
#include "FileNode.h"

class Solution {
public:
    Solution(const std::string& input_file, const size_t& filesystem_size);
    FileNode* const root = new FileNode("/", FileNode::DIR, 0);

    // Sum all the sizes of directories with size <= max_size
    size_t sum_dir_sizes(size_t max_size=std::numeric_limits<size_t>::max()) const;

    /*
        Returns the size of the smallest directory required to achieve space_required.
        Returns -1 if there is no such directory.
    */
    size_t smallest_dir_size(size_t space_required) const;
    
private:
    size_t FILESYSTEM_SIZE;
};
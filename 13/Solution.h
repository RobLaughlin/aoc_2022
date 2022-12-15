#pragma once
#include "../data_structures/TreeNode.h"
#include <vector>

class Solution {
public:
    typedef std::pair<const TreeNode<int>*, const TreeNode<int>*> TreePair;

    static const std::string INPUT_FILENAME;
    
    Solution();

    int count_indices() const;
private:
    static const TreeNode<int>* parse_line(std::string line);

    // Returns 0 if not in order, 1 if in order, and 2 if undecided
    static int in_order(const TreeNode<int>* left, const TreeNode<int>* right);

    std::vector<TreePair> tree_pairs;
};
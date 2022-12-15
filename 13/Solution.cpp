#include "Solution.h"
#include <fstream>
#include <regex>

const std::string Solution::INPUT_FILENAME = "input.txt";

Solution::Solution() 
    : tree_pairs(std::vector<TreePair>())
{
    std::ifstream input(INPUT_FILENAME);

    std::string line;
    TreePair p (nullptr, nullptr);
    while (std::getline(input, line)) {
        if (p.first == nullptr) {
            p.first = Solution::parse_line(line);
        }
        else if (p.second == nullptr) {
            p.second = Solution::parse_line(line);
            this->tree_pairs.push_back(p);
        }
        else {
            p = TreePair(nullptr, nullptr);
        }
    }
}

int Solution::count_indices() const {
    int total = 0;

    for (int i = 0; i < this->tree_pairs.size(); i++) {
        const TreePair& tp = this->tree_pairs[i];
        total += Solution::in_order(tp.first, tp.second) ? i+1 : 0;
    }
    return total;
}

const TreeNode<int>* Solution::parse_line(std::string line) {
    TreeNode<int>* node = nullptr;

    while (line.length() > 0) {
        char c = line[0];
        const bool is_digit = isdigit(c);

        switch (c) {
            case '[':
                if (node == nullptr) { node = TreeNode<int>::Create(-1); }
                else { node = node->add(-1); }
                break;
            case ',': 
                break;
            case ']':
                if (node->parent() != nullptr) {
                    node = node->parent();
                }
                break;
            default:
                if (c == ' ') { break; }

                // Case where we hit an integer
                std::smatch match;
                std::regex_search(line, match, std::regex("\\d+"));

                int val = stoi(match.str());
                node->add(val);

                line = line.substr(match.str().length() - 1);
                break;
        }
        line = line.substr(1);
    }

    return node;
}

int Solution::in_order(const TreeNode<int>* left, const TreeNode<int>* right) {
    if (left->value != -1 && right->value != -1) {
        // Left and right are both integers
        return left->value == right->value ? 2 : left->value < right->value;
    }
    else if (left->value == -1 && right->value == -1) {
        // Left and right are both lists
        const int ls = left->children().size();
        const int rs = right->children().size();

        auto lit = left->children().begin();
        auto rit = right->children().begin();
        for (int i = 0; i < std::min(ls, rs); i++) {
            int result = in_order(*lit, *rit);

            // We have figured out the order, we can return early
            if (result != 2) {
                return result;
            }

            lit++;
            rit++;
        }

        // Order known if sizes are different, but if they're the same we still don't know.
        return ls == rs ? 2 : ls < rs;
    }
    else if (left->value == -1) {
        // Left is a list and right is an integer
        TreeNode<int>* const rnode = TreeNode<int>::Create(-1);
        rnode->add(right->value);

        int result = in_order(left, rnode);
        delete rnode;

        return result;
    }
    else {
        // Left is an integer and right is a list
        TreeNode<int>* const lnode = TreeNode<int>::Create(-1);
        lnode->add(left->value);

        int result = in_order(lnode, right);
        delete lnode;

        return result;   
    }
}
#include "Solution.hpp"
#include <fstream>
#include <unordered_map>

using namespace Solution21;

const std::string Solution::INPUT_FILENAME = "input.txt";
const std::unordered_map<char, char> Solution::INVERSE_OPERATOR = {
    {'+', '-'},
    {'-', '+'},
    {'*', '/'},
    {'/', '*'}
};

Solution::Solution() {
    // Assume the given tree is fully connected so there are no memory leaks...
    
    std::ifstream input(INPUT_FILENAME);
    std::unordered_map<std::string, BinaryNode<int>*> ptr_map;

    std::string line;
    while (std::getline(input, line)) {
        std::string node_name = line.substr(0, 4);

        if (ptr_map.find(node_name) == ptr_map.end()) {
            ptr_map[node_name] = new BinaryNode<int>(0, node_name);
        }

        BinaryNode<int>* const node_ptr = ptr_map[node_name];

        // Check if node is a text node
        const char& c = line[6];
        if (c == '-' || std::isdigit(c)) {
            // If it is a text node, set the value
            node_ptr->value = std::stoi(line.substr(6));
        }
        else {
            // If node is not a text node, set value to the given operator and add children
            node_ptr->value = (int)(line[11]);
            std::string l_child_name = line.substr(6, 4);
            std::string r_child_name = line.substr(13, 4);

            if (ptr_map.find(l_child_name) == ptr_map.end()) {
                ptr_map[l_child_name] = new BinaryNode<int>(0, l_child_name);
            }

            if (ptr_map.find(r_child_name) == ptr_map.end()) {
                ptr_map[r_child_name] = new BinaryNode<int>(0, r_child_name);
            }

            node_ptr->left = NodePtr(ptr_map[l_child_name]);
            node_ptr->right = NodePtr(ptr_map[r_child_name]);
        }
    }
    this->root = NodePtr(ptr_map["root"]);
}

long long Solution::root_yell() const {
    return calc(this->root, false);
}

long long Solution::find_human_number() const {
    const NodePtr* node_ptr = &(this->root);
    long long result = 0;
    
    if ((*node_ptr)->left->find("humn")) {
        result = calc((*node_ptr)->right, false);
        node_ptr = &((*node_ptr)->left);
    }
    else {
        result = calc((*node_ptr)->left, false);
        node_ptr = &((*node_ptr)->right);
    }

    // Solve the equation!
    while ((*node_ptr)->id != "humn") {
        bool human_left = (*node_ptr)->left->find("humn");
        if (human_left) {
            switch ((char)((*node_ptr)->value)) {
                case '+':
                    result -= calc((*node_ptr)->right, false); break;
                case '-':
                    result += calc((*node_ptr)->right, false); break;
                case '*':
                    result /= calc((*node_ptr)->right, false); break;
                case '/':
                    result *= calc((*node_ptr)->right, false); break;
            }
            node_ptr = &((*node_ptr)->left);
        } 
        else {
            switch ((char)((*node_ptr)->value)) {
                case '+':
                    result -= calc((*node_ptr)->left, false); break;
                case '-':
                    result = -(result - calc((*node_ptr)->left, false)); break;
                case '*':
                    result /= calc((*node_ptr)->left, false); break;
                case '/':
                    result = calc((*node_ptr)->left, false) / result; break;
            }
            node_ptr = &((*node_ptr)->right);
        }
    }

    return result;
}

long long Solution::calc(const NodePtr& node, bool inverse, Solution::Memo memo) const {
    if (node->left == nullptr || node->right == nullptr) {
        return (long long)(node->value);
    }

    NodeState state(node->left->id, (char)(node->value), node->right->id);
    if (memo->find(state) != memo->end()) {
        return memo->at(state);
    }

    char v = inverse ? INVERSE_OPERATOR.at((char)(node->value)): (char)(node->value);
    switch (v) {
        case '+':
            (*memo)[state] = calc(node->left, inverse, memo) + calc(node->right, inverse, memo);
            return (*memo)[state];
        case '-':
            (*memo)[state] = calc(node->left, inverse, memo) - calc(node->right, inverse, memo);
            return (*memo)[state];
        case '/':
            (*memo)[state] = calc(node->left, inverse, memo) / calc(node->right, inverse, memo);
            return (*memo)[state];
        case '*':
            (*memo)[state] = calc(node->left, inverse, memo) * calc(node->right, inverse, memo);
            return (*memo)[state];
        default: return 0;
    }

    return 0;
}
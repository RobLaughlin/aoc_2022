#pragma once
#include <stack>
#include <utility>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
class TreeNode {
public:
    TreeNode() = delete;

    // Returns a pointer to node instead of using the constructor
    static TreeNode<T>* Create(T value);

    T value;
    const std::vector<TreeNode<T>*>& children() const;
    TreeNode<T>* parent() const;
    TreeNode<T>* add(T value);
    TreeNode<T>* remove();

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const TreeNode<U>& node);
private:
    TreeNode(T value);

    TreeNode<T>* m_parent;
    std::vector<TreeNode<T>*> m_children;
};

template <typename T>
TreeNode<T>::TreeNode(T value) : value(value), m_parent(nullptr), m_children(std::vector<TreeNode<T>*>()) {}

template <typename T>
TreeNode<T>* TreeNode<T>::Create(T value) {
    return new TreeNode(value);
}

template <typename T>
const std::vector<TreeNode<T>*>& TreeNode<T>::children() const {
    return this->m_children;
}

template <typename T>
TreeNode<T>* TreeNode<T>::parent() const {
    return this->m_parent;
}

template <typename T>
TreeNode<T>* TreeNode<T>::add(T value) {
    // Return the newly added node

    TreeNode<T>* new_node = TreeNode<T>::Create(value);
    new_node->m_parent = this;
    this->m_children.push_back(new_node);

    return new_node;
}

template <typename T>
TreeNode<T>* TreeNode<T>::remove() {
    // Remove this node and return the parent
    TreeNode<T>* parent = this->m_parent;

    // Remove all children
    while (!this->m_children.empty()) {
        TreeNode<T>* const child = this->m_children.back();
        child->remove();
    }
    
    // Sever connection to parent
    if (this->m_parent != nullptr) {
        this->m_parent->m_children.erase(this);
    }

    delete this;
    return parent;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const TreeNode<T>& node) {
    // Print out nodes depth-first
    typedef std::pair<const TreeNode<T>*, int> StackPair;

    std::stack<StackPair> node_stack;
    node_stack.push(StackPair(&node, 0));

    while (!node_stack.empty()) {
        const TreeNode<T>* node = node_stack.top().first;
        int depth = node_stack.top().second;
        node_stack.pop();

        // 2 spaces of padding per depth
        os << std::string(2*depth, '-') << '(' << depth << ") ";

        // Add children to the stack
        for (auto it = node->m_children.begin(); it != node->m_children.end(); it++) {
            node_stack.push(StackPair(*it, depth+1));
        }

        os << node->value;
        os << std::endl;
    }

    return os;
}
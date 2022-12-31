#pragma once
#include <memory>
#include <string>

template <class T>
struct BinaryNode {
    T value;
    std::string id;
    std::unique_ptr<BinaryNode<T>> left;
    std::unique_ptr<BinaryNode<T>> right;

    BinaryNode(T value, std::string id);
    bool find(std::string) const;
private:
    BinaryNode();
};

template <typename T>
BinaryNode<T>::BinaryNode(T value, std::string id) : value(value), id(id), left(nullptr), right(nullptr) {};

template <typename T>
bool BinaryNode<T>::find(std::string id) const {
    // Use DFS
    if (this->id == id) { return true; }
    if (this->left != nullptr && this->left->find(id)) { return true; }
    if (this->right != nullptr && this->right->find(id)) { return true; }
    
    return false;
}
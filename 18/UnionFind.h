#pragma once
#include <unordered_map>

template <class T>
class UnionFind {
public:
    UnionFind();
    void Union(T elem1, T elem2);
    bool connected(T elem1, T elem2);
private:
    std::unordered_map<T, T> parents;
    std::unordered_map<T, long long> sizes;

    T* root(const T& elem);
};

template <typename T>
UnionFind<T>::UnionFind() 
    : parents(std::unordered_map<T, T>()), sizes(std::unordered_map<T, long long>()) {}

template <typename T>
void UnionFind<T>::Union(T elem1, T elem2) {
    if (this->parents.find(elem1) == this->parents.end()) {
        this->parents[elem1] = elem1;
        this->sizes[elem1] = 1;
    }

    if (this->parents.find(elem2) == this->parents.end()) {
        this->parents[elem2] = elem2;
        this->sizes[elem2] = 1;
    }

    T* elem1_root = root(elem1);
    T* elem2_root = root(elem2);
    if (this->sizes[*elem1_root] <= this->sizes[*elem2_root]) {
        this->parents[*elem1_root] = this->parents[*elem2_root];
        this->sizes[*elem2_root] += this->sizes[elem1];
    }
    else {
        this->parents[*elem2_root] = this->parents[*elem1_root];
        this->sizes[*elem1_root] += this->sizes[elem2];
    }
}

template <typename T>
bool UnionFind<T>::connected(T elem1, T elem2) {
    if (this->parents.find(elem1) == this->parents.end() || this->parents.find(elem2) == this->parents.end()){
        return false;
    }

    return *(root(elem1)) == *(root(elem2));
}

template <typename T>
T* UnionFind<T>::root(const T& elem) {
    if (this->parents.find(elem) == this->parents.end()){
        return nullptr;
    }

    if (this->parents[elem] == elem) {
        return &(this->parents[elem]);
    }

    // Flatten the tree while searching for the root
    this->parents[elem] = *(root(this->parents[elem]));
    return &(this->parents[elem]);
}
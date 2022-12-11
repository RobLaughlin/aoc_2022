#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

template <class T>
class Grid {
public:
    Grid(unsigned int rows=0, unsigned int cols=0, T initializer=0);

    T at(unsigned int row, unsigned int col) const;
    bool in_bounds(unsigned int row, unsigned int col) const;
    unsigned int get_rows() const;
    unsigned int get_cols() const;
    void place(T elem, unsigned int row, unsigned int col);

    template <class U>
    friend std::ostream& operator<<(std::ostream& os, const Grid<U>& other);
protected:
    std::vector<std::vector<T>> grid;
    unsigned int rows;
    unsigned int cols;
};

template <class T>
Grid<T>::Grid(unsigned int rows, unsigned int cols, T initializer) 
    : rows(rows), cols(cols)
{
    for (unsigned int r = 0; r < rows; r++) {
        this->grid.push_back(std::vector<T>());
        std::vector<T>& row = this->grid[r];

        for (unsigned int c = 0; c < cols; c++) {
            row.push_back(initializer);
        }
    }
}

template <class T>
T Grid<T>::at(unsigned int row, unsigned int col) const {
    if (!this->in_bounds(row, col)) {
        std::stringstream err;
        err << "index" << '(' << row << ", " << col << ')' << " is out of bounds."; 
        throw std::invalid_argument(err.str());
    }

    return this->grid[row][col];
}

template <class T>
bool Grid<T>::in_bounds(unsigned int row, unsigned int col) const {
    return (row >= 0 && row < this->rows && col >= 0 && col < this->cols);
}

template <class T>
unsigned int Grid<T>::get_rows() const {
    return this->rows;
}

template <class T>
unsigned int Grid<T>::get_cols() const {
    return this->cols;
}

template <class T>
void Grid<T>::place(T elem, unsigned int row, unsigned int col) {
    if (this->in_bounds(row, col)) {
        this->grid[row][col] = elem;
    }
}

template <class T>
std::ostream& operator<<(std::ostream& os, const Grid<T>& other) {
    for (unsigned int r = 0; r < other.rows; r++) {
        os << '[';
        for (unsigned int c = 0; c < other.cols; c++) {
            os << other.at(r, c);
            if (c < other.cols-1) {
                os << ", ";
            }
        }
        os << ']' << std::endl;
    }
    return os;
}
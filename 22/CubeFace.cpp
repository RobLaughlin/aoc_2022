#include "CubeFace.hpp"

Face::Face() : Grid<char>::Grid(), left(this), right(this), top(this), bottom(this), rel_row(0), rel_col(0) {}

Face::Face(int rows, int cols, char initializer, int rel_row, int rel_col) 
    : Grid<char>::Grid(rows, cols, initializer), 
    left(this), right(this), top(this), bottom(this), rel_row(rel_row), rel_col(rel_col)
{}
#include "Grid.h"

struct Face : Grid<char> {
    Face();
    Face(int rows, int cols, char initializer, int rel_row, int rel_col);

    Face* left;
    Face* right;
    Face* top;
    Face* bottom;
    int rel_row = 0;
    int rel_col = 0;
};
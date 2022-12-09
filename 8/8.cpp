#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <unordered_map>
#include "Grid.h"
using namespace std;

static const string INPUT_FILENAME = "input.txt";

pair<unsigned int, unsigned int> grid_dims(const string& filename) {
    int count = 0;
    ifstream input(filename);

    string line;
    while (getline(input, line)) { ++count; }

    return pair<unsigned int, unsigned int>(count, line.length());
}

void fill_grid(Grid<int>& grid, const string& filename) {
    ifstream input(filename);

    string line;
    unsigned int row = 0;
    while (getline(input, line)) {
        for (unsigned int col = 0; col < line.length(); col++) {
            int c = line[col] - '0';
            grid.place(c, row, col);
        }
        row++;
    }
}

int count_visible(
    const Grid<bool>& top_mask, 
    const Grid<bool>& right_mask,
    const Grid<bool>& bottom_mask,
    const Grid<bool>& left_mask) {

        int num_visible = 0;
        for (int r = 0; r < top_mask.get_rows(); r++) {
            for (int c = 0; c < top_mask.get_cols(); c++) {
                bool x1 = top_mask.at(r, c);
                bool x2 = right_mask.at(r, c);
                bool x3 = bottom_mask.at(r, c);
                bool x4 = left_mask.at(r, c);

                num_visible += (int)(x1 || x2 || x3 || x4);
            }
        }
        return num_visible;
}

void left_visible_mask(const Grid<int>& grid, Grid<bool>& mask) {
    for (int r = 0; r < grid.get_rows(); r++) {
        int max = -1;

        for (int c = 0; c < grid.get_cols(); c++) {
            int tree = grid.at(r, c);
            if (tree > max) {
                max = tree;
                mask.place(true, r, c);
            }
        }
    }
}

void top_visible_mask(const Grid<int>& grid, Grid<bool>& mask) {
    for (int c = 0; c < grid.get_cols(); c++) {
        int max = -1;

        for (int r = 0; r < grid.get_rows(); r++) {
            int tree = grid.at(r, c);
            if (tree > max) {
                max = tree;
                mask.place(true, r, c);
            }
        }
    }
}

void right_visible_mask(const Grid<int>& grid, Grid<bool>& mask) {
    for (int r = 0; r < grid.get_rows(); r++) {
        int max = -1;

        for (int c = grid.get_cols()-1; c >= 0; c--) {
            int tree = grid.at(r, c);
            if (tree > max) {
                max = tree;
                mask.place(true, r, c);
            }
        }
    }
}

void bottom_visible_mask(const Grid<int>& grid, Grid<bool>& mask) {
    for (int c = 0; c < grid.get_cols(); c++) {
        int max = -1;

        for (int r = grid.get_rows()-1; r >= 0; r--) {
            int tree = grid.at(r, c);
            if (tree > max) {
                max = tree;
                mask.place(true, r, c);
            }
        }
    }
}

int main() {
    pair<unsigned int, unsigned int> dims = grid_dims(INPUT_FILENAME);
    Grid<int> grid = Grid<int>(dims.first, dims.second, 0);

    Grid<bool> left_mask = Grid<bool>(dims.first, dims.second, false);
    Grid<bool> right_mask = Grid<bool>(dims.first, dims.second, false);
    Grid<bool> top_mask = Grid<bool>(dims.first, dims.second, false);
    Grid<bool> bottom_mask = Grid<bool>(dims.first, dims.second, false);

    fill_grid(grid, INPUT_FILENAME);

    left_visible_mask(grid, left_mask);
    right_visible_mask(grid, right_mask);
    top_visible_mask(grid, top_mask);
    bottom_visible_mask(grid, bottom_mask);

    // cout << left_mask << endl;
    // cout << right_mask << endl;
    // cout << top_mask << endl;
    // cout << bottom_mask << endl;
    // cout << grid << endl;
    cout << count_visible(top_mask, right_mask, bottom_mask, left_mask) << endl;
    // cout << count_ones(mask) << endl;
    return 0;
}
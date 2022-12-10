#include "Solution.h"

const std::string Solution::INPUT_FILENAME = "input.txt";

Solution::Solution() {
    std::ifstream input(INPUT_FILENAME);
    std::pair<int, int> grid_dims = this->grid_dims();

    this->grid = Grid<int>(grid_dims.first, grid_dims.second, 0);

    std::string line;
    int row = 0;
    while (getline(input, line)) {
        for (int col = 0; col < line.length(); col++) {
            int c = line[col] - '0';
            this->grid.place(c, row, col);
        }
        row++;
    }
}

int Solution::count_visible() const {
    int num_visible = 0;

    Grid<bool> mask = Grid<bool>(this->grid.get_rows(), this->grid.get_cols(), false);
    this->apply_visibility_mask(mask, LEFT);
    this->apply_visibility_mask(mask, TOP);
    this->apply_visibility_mask(mask, RIGHT);
    this->apply_visibility_mask(mask, DOWN);

    for (int r = 0; r < this->grid.get_rows(); r++) {
        for (int c = 0; c < this->grid.get_cols(); c++) {
            num_visible += (int)mask.at(r, c);
        }
    }

    return num_visible;
}

int Solution::scenic_score(int row, int col) const {
    int r = row;
    int c  = col;
    int elem = grid.at(r, c);

    auto calc_score = [this, &elem, &r, &c] (int& idx, int default_idx, int inc) {
        int score = 0;

        idx += inc;
        while (this->grid.in_bounds(r, c)) {
            score++;
            
            if (this->grid.at(r, c) >= elem) { break; }
            idx += inc;
        }
        idx = default_idx;

        return score;
    };

    int score = 1;
    score *= calc_score(c, col, 1);
    score *= calc_score(c, col, -1);
    score *= calc_score(r, row, 1);
    score *= calc_score(r, row, -1);

    return score;
}

int Solution::max_scenic_score() const {
    int max_score = 0;

    for (int r = 0; r < this->grid.get_rows(); r++) {
        for (int c = 0; c < this->grid.get_cols(); c++) {
            int score = this->scenic_score(r, c);
            max_score = score > max_score ? score : max_score;
        }
    }

    return max_score;
}

std::pair<int, int> Solution::grid_dims() {
    int count = 0;
    std::ifstream input(INPUT_FILENAME);

    std::string line;
    while (getline(input, line)) { ++count; }

    return std::pair<int, int>(count, line.length());
}

void Solution::apply_visibility_mask(Grid<bool>& mask, Direction direction) const {
    switch (direction) {
        case LEFT:
            for (int r = 0; r < this->grid.get_rows(); r++) {
                int max = -1;

                for (int c = 0; c < this->grid.get_cols(); c++) {
                    int tree = this->grid.at(r, c);
                    if (tree > max) {
                        max = tree;
                        mask.place(true, r, c);
                    }
                }
            }
            break;
        case TOP:
            for (int c = 0; c < this->grid.get_cols(); c++) {
                int max = -1;

                for (int r = 0; r < this->grid.get_rows(); r++) {
                    int tree = this->grid.at(r, c);
                    if (tree > max) {
                        max = tree;
                        mask.place(true, r, c);
                    }
                }
            }
            break;
        case RIGHT:
            for (int r = 0; r < this->grid.get_rows(); r++) {
                int max = -1;

                for (int c = this->grid.get_cols()-1; c >= 0; c--) {
                    int tree = this->grid.at(r, c);
                    if (tree > max) {
                        max = tree;
                        mask.place(true, r, c);
                    }
                }
            }
            break;
        case DOWN:
            for (int c = 0; c < this->grid.get_cols(); c++) {
                int max = -1;

                for (int r = this->grid.get_rows()-1; r >= 0; r--) {
                    int tree = this->grid.at(r, c);
                    if (tree > max) {
                        max = tree;
                        mask.place(true, r, c);
                    }
                }
            }
            break;
        default: break;
    }
}
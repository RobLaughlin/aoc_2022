#include "Solution.hpp"
#include <math.h>
#include <fstream>
#include <regex>

using namespace Solution22;

Solution::Solution(Solution::Input input_type) 
    : m_input(input_type)
{
    const std::string input_filename = input_type == AOC_INPUT ? "input.txt" : "input2.txt";
    
    std::ifstream input(input_filename);
    int num_cols = 0;
    int num_rows = 0;

    std::string line;

    // Get the dimensions of the grid first
    while (std::getline(input, line)) {
        if (line == "") { break; }
        num_cols = std::max(num_cols, (int)(line.length()));
        num_rows++;
    }
    input.clear();
    input.seekg(0);
    
    this->m_grid = Grid<char>(num_rows, num_cols, ' ');

    // Now fill the grid
    int row = 0;
    while (std::getline(input, line)) {
        if (line == "") { break; }

        for (int col = 0; col < line.length(); col++) {
            this->m_grid.place(line[col], row, col);
        }
        row++;
    }

    // Fill in the moves
    std::getline(input, line);
    std::string moves_str = 'R' + line;

    while (moves_str.length() > 0) {
        std::smatch match;

        char direction = moves_str[0];
        moves_str = moves_str.substr(1);

        std::regex_search(moves_str, match, std::regex("\\d+"));
        int move = std::stoi(match.str());
        moves_str = match.suffix().str();

        Move m(direction, move);
        this->m_moves.push_back(m);
    }

    // Break up the grid into cube faces
    int face_size = input_type == SAMPLE_INPUT ? 4 : 50;
    if (input_type == SAMPLE_INPUT) {
        this->m_faces[0] = Face(face_size, face_size, ' ', 0, 2*face_size);
        this->m_faces[1] = Face(face_size, face_size, ' ', face_size, 0);
        this->m_faces[2] = Face(face_size, face_size, ' ', face_size, face_size);
        this->m_faces[3] = Face(face_size, face_size, ' ', face_size, 2*face_size);
        this->m_faces[4] = Face(face_size, face_size, ' ', 2*face_size, 2*face_size);
        this->m_faces[5] = Face(face_size, face_size, ' ', 2*face_size, 3*face_size);
    }
    else {
        this->m_faces[0] = Face(face_size, face_size, ' ', 0, face_size);
        this->m_faces[1] = Face(face_size, face_size, ' ', 0, 2*face_size);
        this->m_faces[2] = Face(face_size, face_size, ' ', face_size, face_size);
        this->m_faces[3] = Face(face_size, face_size, ' ', 2*face_size, face_size);
        this->m_faces[4] = Face(face_size, face_size, ' ', 2*face_size, 0);
        this->m_faces[5] = Face(face_size, face_size, ' ', 3*face_size, 0);  
    }

    // Copy all faces to cube faces
    this->m_cube_faces = m_faces;

    // By default, make the faces wrap around to themselves
    for (int i = 0; i < this->m_faces.size(); i++) {
        this->m_faces[i].left   = &(this->m_faces[i]);
        this->m_faces[i].top    = &(this->m_faces[i]);
        this->m_faces[i].right  = &(this->m_faces[i]);
        this->m_faces[i].bottom = &(this->m_faces[i]);

        this->m_cube_faces[i].left   = &(this->m_cube_faces[i]);
        this->m_cube_faces[i].top    = &(this->m_cube_faces[i]);
        this->m_cube_faces[i].right  = &(this->m_cube_faces[i]);
        this->m_cube_faces[i].bottom = &(this->m_cube_faces[i]);
    }

    // Fill in the faces
    for (int r = 0; r < face_size; r++) {
        for (int c = 0; c < face_size; c++) {
            for (int i = 0; i < this->m_faces.size(); i++) {
                const int& rel_row = this->m_faces[i].rel_row;
                const int& rel_col = this->m_faces[i].rel_col;
                const char& chr = this->m_grid.at(rel_row+r, rel_col+c);
                
                this->m_faces[i].place(chr, r, c);
                this->m_cube_faces[i].place(chr, r, c);
            }
        }
    }

    // Connect the faces depending on the input type
    if (input_type == SAMPLE_INPUT) {
        this->m_faces[0].bottom = &(this->m_faces[3]);
        this->m_faces[0].top = &(this->m_faces[4]);

        this->m_faces[1].right = &(this->m_faces[2]);
        this->m_faces[1].left = &(this->m_faces[3]);

        this->m_faces[2].right = &(this->m_faces[3]);
        this->m_faces[2].left = &(this->m_faces[1]);

        this->m_faces[3].right = &(this->m_faces[1]);
        this->m_faces[3].left = &(this->m_faces[2]);
        this->m_faces[3].top = &(this->m_faces[0]);
        this->m_faces[3].bottom = &(this->m_faces[4]);

        this->m_faces[4].left = &(this->m_faces[5]);
        this->m_faces[4].right = &(this->m_faces[5]);
        this->m_faces[4].top = &(this->m_faces[3]);
        this->m_faces[4].bottom = &(this->m_faces[0]);

        this->m_faces[5].left = &(this->m_faces[4]);
        this->m_faces[5].right = &(this->m_faces[4]);

        // Make the same wrap arounds for the cube faces
        this->m_cube_faces[0].bottom = &(this->m_cube_faces[3]);
        this->m_cube_faces[0].top = &(this->m_cube_faces[4]);

        this->m_cube_faces[1].right = &(this->m_cube_faces[2]);
        this->m_cube_faces[1].left = &(this->m_cube_faces[3]);

        this->m_cube_faces[2].right = &(this->m_cube_faces[3]);
        this->m_cube_faces[2].left = &(this->m_cube_faces[1]);

        this->m_cube_faces[3].right = &(this->m_cube_faces[1]);
        this->m_cube_faces[3].left = &(this->m_cube_faces[2]);
        this->m_cube_faces[3].top = &(this->m_cube_faces[0]);
        this->m_cube_faces[3].bottom = &(this->m_cube_faces[4]);

        this->m_cube_faces[4].left = &(this->m_cube_faces[5]);
        this->m_cube_faces[4].right = &(this->m_cube_faces[5]);
        this->m_cube_faces[4].top = &(this->m_cube_faces[3]);
        this->m_cube_faces[4].bottom = &(this->m_cube_faces[0]);

        this->m_cube_faces[5].left = &(this->m_cube_faces[4]);
        this->m_cube_faces[5].right = &(this->m_cube_faces[4]);

        // Now make the wrappings specific to cubes.
        this->m_cube_faces[0].top = &(this->m_cube_faces[1]);
        this->m_cube_faces[0].left = &(this->m_cube_faces[2]);
        this->m_cube_faces[0].right = &(this->m_cube_faces[5]);

        this->m_cube_faces[1].top = &(this->m_cube_faces[0]);
        this->m_cube_faces[1].left = &(this->m_cube_faces[5]);
        this->m_cube_faces[1].bottom = &(this->m_cube_faces[4]);

        this->m_cube_faces[2].top = &(this->m_cube_faces[0]);
        this->m_cube_faces[2].bottom = &(this->m_cube_faces[4]);

        this->m_cube_faces[3].right = &(this->m_cube_faces[5]);

        this->m_cube_faces[4].left = &(this->m_cube_faces[2]);
        this->m_cube_faces[4].bottom = &(this->m_cube_faces[1]);

        this->m_cube_faces[5].bottom = &(this->m_cube_faces[1]);
        this->m_cube_faces[5].right = &(this->m_cube_faces[0]);
        this->m_cube_faces[5].top = &(this->m_cube_faces[3]);
    }
    else {
        this->m_faces[0].top = &(this->m_faces[3]);
        this->m_faces[0].right = &(this->m_faces[1]);
        this->m_faces[0].bottom = &(this->m_faces[2]);
        this->m_faces[0].left = &(this->m_faces[1]);

        this->m_faces[1].left = &(this->m_faces[0]);
        this->m_faces[1].right = &(this->m_faces[0]);

        this->m_faces[2].top = &(this->m_faces[0]);
        this->m_faces[2].bottom = &(this->m_faces[3]);

        this->m_faces[3].left = &(this->m_faces[4]);
        this->m_faces[3].top = &(this->m_faces[2]);
        this->m_faces[3].right = &(this->m_faces[4]);
        this->m_faces[3].bottom = &(this->m_faces[0]);

        this->m_faces[4].right = &(this->m_faces[3]);
        this->m_faces[4].bottom = &(this->m_faces[5]);
        this->m_faces[4].left = &(this->m_faces[3]);
        this->m_faces[4].top = &(this->m_faces[5]);

        this->m_faces[5].top = &(this->m_faces[4]);
        this->m_faces[5].bottom = &(this->m_faces[4]);

        this->m_cube_faces[0].top = &(this->m_cube_faces[3]);
        this->m_cube_faces[0].right = &(this->m_cube_faces[1]);
        this->m_cube_faces[0].bottom = &(this->m_cube_faces[2]);
        this->m_cube_faces[0].left = &(this->m_cube_faces[1]);

        this->m_cube_faces[1].left = &(this->m_cube_faces[0]);
        this->m_cube_faces[1].right = &(this->m_cube_faces[0]);

        this->m_cube_faces[2].top = &(this->m_cube_faces[0]);
        this->m_cube_faces[2].bottom = &(this->m_cube_faces[3]);

        this->m_cube_faces[3].left = &(this->m_cube_faces[4]);
        this->m_cube_faces[3].top = &(this->m_cube_faces[2]);
        this->m_cube_faces[3].right = &(this->m_cube_faces[4]);
        this->m_cube_faces[3].bottom = &(this->m_cube_faces[0]);

        this->m_cube_faces[4].right = &(this->m_cube_faces[3]);
        this->m_cube_faces[4].bottom = &(this->m_cube_faces[5]);
        this->m_cube_faces[4].left = &(this->m_cube_faces[3]);
        this->m_cube_faces[4].top = &(this->m_cube_faces[5]);

        this->m_cube_faces[5].top = &(this->m_cube_faces[4]);
        this->m_cube_faces[5].bottom = &(this->m_cube_faces[4]);

        this->m_cube_faces[0].left = &(this->m_cube_faces[4]);
        this->m_cube_faces[0].top = &(this->m_cube_faces[5]);

        this->m_cube_faces[1].top = &(this->m_cube_faces[5]);
        this->m_cube_faces[1].right = &(this->m_cube_faces[3]);
        this->m_cube_faces[1].bottom = &(this->m_cube_faces[2]);

        this->m_cube_faces[2].left = &(this->m_cube_faces[4]);
        this->m_cube_faces[2].right = &(this->m_cube_faces[1]);

        this->m_cube_faces[3].right = &(this->m_cube_faces[1]);
        this->m_cube_faces[3].bottom = &(this->m_cube_faces[5]);

        this->m_cube_faces[4].left = &(this->m_cube_faces[0]);
        this->m_cube_faces[4].top = &(this->m_cube_faces[2]);

        this->m_cube_faces[5].left = &(this->m_cube_faces[0]);
        this->m_cube_faces[5].bottom = &(this->m_cube_faces[1]);
        this->m_cube_faces[5].right = &(this->m_cube_faces[3]);
    }
}


long long Solution::find_password(bool cube) const {
    const Face* pFace = cube ? &(this->m_cube_faces[0]) : &(this->m_faces[0]);
    State state {0, 0, UP, pFace};

    for (const Move& move : this->m_moves) {
        state = next_state(state, move, cube);
    }

    long long pwd = 0;
    pwd += 1000*(state.face->rel_row + state.row + 1);
    pwd += 4*(state.face->rel_col + state.col + 1);
    pwd += (long long)(state.direction);
    return pwd;
}

Solution::State Solution::next_state(const Solution::State& prev_state, const Solution::Move& move, bool cube) const {
    // Face size
    const int fs = this->m_faces[0].get_rows();

    const char& turn = move.first;
    int moves_forward = move.second;
    const int change = turn == 'R' ? 1 : -1;
    
    int row = prev_state.row;
    int col = prev_state.col;
    Direction direction = prev_state.direction;
    const Face* pFace = prev_state.face;

    // Make a turn
    direction = (Direction)((direction + change + 4) % 4);

    // Walk in this direction
    while (moves_forward > 0) {
        int next_row = row;
        int next_col = col;
        Direction next_direction = direction;

        switch (direction) {
            case UP:    next_row--; break;
            case RIGHT: next_col++; break;
            case DOWN:  next_row++; break;
            case LEFT:  next_col--; break;
        }
        
        // Check if we need to change faces
        const Face* next_face = pFace;
        if (!cube) {
            if (next_row < 0) {
                next_face = pFace->top;
                next_row = next_face->get_rows()-1;
            }
            else if (next_row >= pFace->get_rows()) {
                next_face = pFace->bottom;
                next_row = 0;
            }
            else if (next_col < 0) {
                next_face = pFace->left;
                next_col = next_face->get_cols()-1;
            }
            else if (next_col >= pFace->get_cols()) {
                next_face = pFace->right;
                next_col = 0;
            }
        }

        // We're going to need to change the state and map edges differently when we work with the cube form
        else if (m_input == SAMPLE_INPUT) {
            // Wrap the top face
            if (pFace->rel_row == 0 && pFace->rel_col == 2*fs) {
                if (next_row < 0) {
                    next_direction = DOWN;
                    next_face = pFace->top;
                    next_row = 0;
                    next_col = fs-col-1;
                }
                else if (next_row >= pFace->get_rows()) {
                    next_direction = DOWN;
                    next_face = pFace->bottom;
                    next_row = 0;
                    next_col = col;
                }
                else if (next_col < 0) {
                    next_direction = DOWN;
                    next_face = pFace->left;
                    next_row = 0;
                    next_col = row;
                }
                else if (next_col >= pFace->get_cols()) {
                    next_direction = LEFT;
                    next_face = pFace->right;
                    next_row = fs-row-1;
                    next_col = fs-1;
                }
            }
            // Wrap the left face
            else if (pFace->rel_row == fs && pFace->rel_col == 0) {
                if (next_row < 0) {
                    next_direction = DOWN;
                    next_face = pFace->top;
                    next_row = 0;
                    next_col = fs-col-1;
                }
                else if (next_row >= pFace->get_rows()) {
                    next_direction = UP;
                    next_face = pFace->bottom;
                    next_row = fs-1;
                    next_col = fs-col-1;
                }
                else if (next_col < 0) {
                    next_direction = UP;
                    next_face = pFace->left;
                    next_row = fs-1;
                    next_col = fs-row-1;
                }
                else if (next_col >= pFace->get_cols()) {
                    next_direction = RIGHT;
                    next_face = pFace->right;
                    next_row = row;
                    next_col = 0;
                }
            }
            // Wrap the middle-left face
            else if (pFace->rel_row == fs && pFace->rel_col == fs) {
                if (next_row < 0) {
                    next_direction = RIGHT;
                    next_face = pFace->top;
                    next_row = col;
                    next_col = 0;
                }
                else if (next_row >= pFace->get_rows()) {
                    next_direction = RIGHT;
                    next_face = pFace->bottom;
                    next_row = fs-1-col;
                    next_col = 0;
                }
                else if (next_col < 0) {
                    next_direction = LEFT;
                    next_face = pFace->left;
                    next_row = row;
                    next_col = fs-1;
                }
                else if (next_col >= pFace->get_cols()) {
                    next_direction = RIGHT;
                    next_face = pFace->right;
                    next_row = row;
                    next_col = 0;
                }
            }
            // Wrap the middle face
            else if (pFace->rel_row == fs && pFace->rel_col == 2*fs) {
                if (next_row < 0) {
                    next_direction = UP;
                    next_face = pFace->top;
                    next_row = fs-1;
                    next_col = col;
                }
                else if (next_row >= pFace->get_rows()) {
                    next_direction = DOWN;
                    next_face = pFace->bottom;
                    next_row = 0;
                    next_col = col;
                }
                else if (next_col < 0) {
                    next_direction = LEFT;
                    next_face = pFace->left;
                    next_row = row;
                    next_col = fs-1;
                }
                else if (next_col >= pFace->get_cols()) {
                    next_direction = DOWN;
                    next_face = pFace->right;
                    next_row = 0;
                    next_col = fs-1-row;
                }
            }
            // Wrap the bottom face
            else if (pFace->rel_row == 2*fs && pFace->rel_col == 2*fs) {
                if (next_row < 0) {
                    next_direction = UP;
                    next_face = pFace->top;
                    next_row = fs-1;
                    next_col = col;
                }
                else if (next_row >= pFace->get_rows()) {
                    next_direction = UP;
                    next_face = pFace->bottom;
                    next_row = fs-1;
                    next_col = fs-1-col;
                }
                else if (next_col < 0) {
                    next_direction = UP;
                    next_face = pFace->left;
                    next_row = fs-1;
                    next_col = fs-1-row;
                }
                else if (next_col >= pFace->get_cols()) {
                    next_direction = RIGHT;
                    next_face = pFace->right;
                    next_row = row;
                    next_col = 0;
                }
            }
            // Wrap the bottom-right face
            else if (pFace->rel_row == 2*fs && pFace->rel_col == 3*fs) {
                if (next_row < 0) {
                    next_direction = LEFT;
                    next_face = pFace->top;
                    next_row = fs-1-col;
                    next_col = fs-1;
                }
                else if (next_row >= pFace->get_rows()) {
                    next_direction = RIGHT;
                    next_face = pFace->bottom;
                    next_row = fs-1-col;
                    next_col = 0;
                }
                else if (next_col < 0) {
                    next_direction = LEFT;
                    next_face = pFace->left;
                    next_row = row;
                    next_col = fs-1;
                }
                else if (next_col >= pFace->get_cols()) {
                    next_direction = LEFT;
                    next_face = pFace->right;
                    next_row = fs-1-row;
                    next_col = fs-1;
                }
            }
        }
        else {
            if (pFace->rel_row == 0 && pFace->rel_col == fs) {
                if (next_row < 0) {
                    next_direction = RIGHT;
                    next_face = pFace->top;
                    next_row = col;
                    next_col = 0;
                }
                else if (next_row >= pFace->get_rows()) {
                    next_direction = DOWN;
                    next_face = pFace->bottom;
                    next_row = 0;
                    next_col = col;
                }
                else if (next_col < 0) {
                    next_direction = RIGHT;
                    next_face = pFace->left;
                    next_row = fs-1-row;
                    next_col = 0;
                }
                else if (next_col >= pFace->get_cols()) {
                    next_direction = RIGHT;
                    next_face = pFace->right;
                    next_row = row;
                    next_col = 0;
                }
            }
            else if (pFace->rel_row == 0 && pFace->rel_col == 2*fs) {
                if (next_row < 0) {
                    next_direction = UP;
                    next_face = pFace->top;
                    next_row = fs-1;
                    next_col = col;
                }
                else if (next_row >= pFace->get_rows()) {
                    next_direction = LEFT;
                    next_face = pFace->bottom;
                    next_row = col;
                    next_col = fs-1;
                }
                else if (next_col < 0) {
                    next_direction = LEFT;
                    next_face = pFace->left;
                    next_row = row;
                    next_col = fs-1;
                }
                else if (next_col >= pFace->get_cols()) {
                    next_direction = LEFT;
                    next_face = pFace->right;
                    next_row = fs-1-row;
                    next_col = fs-1;
                }
            }
            else if (pFace->rel_row == fs && pFace->rel_col == fs) {
                if (next_row < 0) {
                    next_direction = UP;
                    next_face = pFace->top;
                    next_row = fs-1;
                    next_col = col;
                }
                else if (next_row >= pFace->get_rows()) {
                    next_direction = DOWN;
                    next_face = pFace->bottom;
                    next_row = 0;
                    next_col = col;
                }
                else if (next_col < 0) {
                    next_direction = DOWN;
                    next_face = pFace->left;
                    next_row = 0;
                    next_col = row;
                }
                else if (next_col >= pFace->get_cols()) {
                    next_direction = UP;
                    next_face = pFace->right;
                    next_row = fs-1;
                    next_col = row;
                }
            }
            else if (pFace->rel_row == 2*fs && pFace->rel_col == fs) {
                if (next_row < 0) {
                    next_direction = UP;
                    next_face = pFace->top;
                    next_row = fs-1;
                    next_col = col;
                }
                else if (next_row >= pFace->get_rows()) {
                    next_direction = LEFT;
                    next_face = pFace->bottom;
                    next_row = col;
                    next_col = fs-1;
                }
                else if (next_col < 0) {
                    next_direction = LEFT;
                    next_face = pFace->left;
                    next_row = row;
                    next_col = fs-1;
                }
                else if (next_col >= pFace->get_cols()) {
                    next_direction = LEFT;
                    next_face = pFace->right;
                    next_row = fs-1-row;
                    next_col = fs-1;
                }
            }
            else if (pFace->rel_row == 2*fs && pFace->rel_col == 0) {
                if (next_row < 0) {
                    next_direction = RIGHT;
                    next_face = pFace->top;
                    next_row = col;
                    next_col = 0;
                }
                else if (next_row >= pFace->get_rows()) {
                    next_direction = DOWN;
                    next_face = pFace->bottom;
                    next_row = 0;
                    next_col = col;
                }
                else if (next_col < 0) {
                    next_direction = RIGHT;
                    next_face = pFace->left;
                    next_row = fs-1-row;
                    next_col = 0;
                }
                else if (next_col >= pFace->get_cols()) {
                    next_direction = RIGHT;
                    next_face = pFace->right;
                    next_row = row;
                    next_col = 0;
                }
            }
            else if (pFace->rel_row == 3*fs && pFace->rel_col == 0) {
                if (next_row < 0) {
                    next_direction = UP;
                    next_face = pFace->top;
                    next_row = fs-1;
                    next_col = col;
                }
                else if (next_row >= pFace->get_rows()) {
                    next_direction = DOWN;
                    next_face = pFace->bottom;
                    next_row = 0;
                    next_col = col;
                }
                else if (next_col < 0) {
                    next_direction = DOWN;
                    next_face = pFace->left;
                    next_row = 0;
                    next_col = row;
                }
                else if (next_col >= pFace->get_cols()) {
                    next_direction = UP;
                    next_face = pFace->right;
                    next_row = fs-1;
                    next_col = row;
                }
            }
        }

        // Check if the next position is blocked
        if (next_face->at(next_row, next_col) != '#') {
            row = next_row;
            col = next_col;
            pFace = next_face;
            direction = next_direction;
        }
        else {
            // If we ever get blocked, why move anymore?
            moves_forward = 0;
        }
        moves_forward--;
    }

    return State{row, col, direction, pFace};
}
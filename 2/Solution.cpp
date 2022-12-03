#include <iostream>
#include <fstream>
#include <vector>
#include "Solution.h"
using namespace std;

Solution::Solution(const string& input_filename) {
    vector<Game> games = vector<Game>();

    ifstream input;
    input.open("input.txt");
    if (!input.is_open()) {
        cerr << "Error opening input file" << endl;
        input.close();
        throw invalid_argument("Error opening input file");
    }

    string line;
    while (getline(input, line)) {
        Game game = Game(line[2], line[0]);
        games.push_back(game);
    }

    input.close();
    this->games = games;
}

array<int, 2> Solution::solve() {
    array<int, 2> solution = {0,0};

    // Add up the scores for the solution to each part
    for (Game game : this->games) {
        solution[0] += game.score(false);
        solution[1] += game.score(true);
    }

    return solution;
}
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <array>

using namespace std;

const string INPUT_FILENAME = "input.txt";

class Game {
public:
    Game(char me, char opponent, bool replace_move=false) {
        this->me_ = me;
        this->opponent_ = opponent;

        if (replace_move) {
            const string key = {me, opponent};
            this->me_ = this->OPTIMAL_MOVE.at(key);
        }
    }

    char me() const { return this->me_; }
    char opponent() const { return this->opponent_; }

    int score() {
        int score = 0;
        const char me = this->me_;
        const char opponent = this->opponent_;

        switch (me) {
            case 'X': score += 1; break;
            case 'Y': score += 2; break;
            case 'Z': score += 3; break;
            default: throw invalid_argument("Invalid Game");
        }

        if ((me == 'Y' && opponent == 'A') || (me == 'X' && opponent == 'C') || (me == 'Z' && opponent == 'B')) {
            score += 6;
        }
        else if ((me == 'Z' && opponent == 'C') || (me == 'Y' && opponent == 'B') || (me == 'X' && opponent == 'A'))
        {
            score += 3;
        }

        return score;
    }

    friend ostream& operator<<(ostream& os, const Game& game) {
        os << "(" << game.me() << ", " << game.opponent() << ")";
        return os;
    }

private:
    char me_;
    char opponent_;
    static const unordered_map<string, char> OPTIMAL_MOVE;
};

const unordered_map<string, char> Game::OPTIMAL_MOVE = {
    // X -> lose, Y -> draw, Z-> win
    {"XA", 'Z'}, {"XB", 'X'}, {"XC", 'Y'},
    {"YA", 'X'}, {"YB", 'Y'}, {"YC", 'Z'},
    {"ZA", 'Y'}, {"ZB", 'Z'}, {"ZC", 'X'} 
};

array<vector<Game>, 2> preprocess(const string& input_file) {
    array<vector<Game>, 2> data = {vector<Game>(), vector<Game>()};

    ifstream input;
    input.open("input.txt");
    if (!input.is_open()) {
        cerr << "Error opening input file" << endl;
        input.close();
        return data;
    }

    string line;
    while (getline(input, line)) {
        Game game = Game(line[2], line[0]);
        Game gameReplaced = Game(line[2], line[0], true);
        data.at(0).push_back(game);
        data.at(1).push_back(gameReplaced);
    }

    input.close();
    return data;
};

int main() {
    array<vector<Game>, 2> data = preprocess(INPUT_FILENAME);
    vector<Game> games1 = data[0];
    vector<Game> games2 = data[1];

    int score1 = 0;
    int score2 = 0;
    for (int i = 0; i < games1.size(); i++) {
        score1 += games1[i].score();
        score2 += games2[i].score();
    }

    cout << score1 << endl;
    cout << score2 << endl;
    return 0;
}
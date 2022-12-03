#include "Game.h"
using namespace std;

Game::Game(char me, char opponent) {
    this->me_ = me;
    this->opponent_ = opponent;
}

char Game::me() const { return this->me_; }
char Game::opponent() const { return this->opponent_; }

int Game::score(bool replace_move) {
    int score = 0;
    char me = this->me_;
    const char opponent = this->opponent_;

    if (replace_move) {
        const string key = {me, opponent};
        me = this->OPTIMAL_MOVE.at(key);
    }
    
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

ostream& operator<<(ostream& os, const Game& game) {
    os << "(" << game.me() << ", " << game.opponent() << ")";
    return os;
}

const unordered_map<string, char> Game::OPTIMAL_MOVE = {
    // X -> lose, Y -> draw, Z-> win
    {"XA", 'Z'}, {"XB", 'X'}, {"XC", 'Y'},
    {"YA", 'X'}, {"YB", 'Y'}, {"YC", 'Z'},
    {"ZA", 'Y'}, {"ZB", 'Z'}, {"ZC", 'X'} 
};
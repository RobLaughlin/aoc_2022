#pragma once
#include <iostream>
#include <unordered_map>
#include <string>

class Game {
public:
    Game(char me, char opponent);
    char me() const;
    char opponent() const;

    // replace_move is used to change the behavior for how to interpret the move you should play.
    // false is the default, which is calculate the score by just playing the suggested move.
    // true is the other option, which is to adjust to win/lose/draw based on the suggested move.
    int score(bool replace_move=false);
    
    friend std::ostream& operator<<(std::ostream& os, const Game& game);
private:
    char me_;
    char opponent_;
    static const std::unordered_map<std::string, char> OPTIMAL_MOVE;
};
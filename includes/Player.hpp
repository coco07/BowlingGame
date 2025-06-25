#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include "BowlingGame.hpp"

class Player {
public:
    explicit Player(const std::string& name);

    void roll(int pins);
    int score() const;
    const std::string& getName() const;
    bool isGameComplete() const;
    const std::vector<Frame>& getFrames() const;

private:
    std::string name;
    BowlingGame game;
};

#endif


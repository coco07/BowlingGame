#include "Player.hpp"
#include <stdexcept>

Player::Player(const std::string& name) : name(name) {}

void Player::roll(int pins) {
    game.roll(pins);
}

int Player::score() const {
    return game.score();
}

const std::string& Player::getName() const {
    return name;
}

bool Player::isGameComplete() const {
    return game.isComplete();
}

const std::vector<Frame>& Player::getFrames() const {
    return game.getFrames();
}

#include "Frame.hpp"
#include <stdexcept>

Frame::Frame(bool isFinal) : finalFrame(isFinal) {}

void Frame::roll(int pins) {
    if (pins < 0 || pins > 10)
        throw std::invalid_argument("Pin count must be between 0 and 10.");

    if (!finalFrame) {
        if (rolls.size() == 1 && rolls[0] + pins > 10)
            throw std::invalid_argument("Cannot knock down more than 10 pins in a standard frame.");
    }

    if (finalFrame) {
        if (rolls.size() == 2 && (rolls[0] + rolls[1] < 10))
            throw std::out_of_range("Only two rolls allowed if no strike/spare in final frame.");
        if (rolls.size() >= 3)
            throw std::out_of_range("Maximum of three rolls allowed in final frame.");
    } else {
        if (isComplete())
            throw std::out_of_range("Cannot roll in a completed frame.");
    }

    rolls.push_back(pins);
}

int Frame::score() const {
    int total = 0;
    for (int pin : rolls) total += pin;
    return total;
}

bool Frame::isStrike() const {
    return !finalFrame && rolls.size() == 1 && rolls[0] == 10;
}

bool Frame::isSpare() const {
    return !finalFrame && rolls.size() == 2 && rolls[0] + rolls[1] == 10;
}

bool Frame::isComplete() const {
    if (finalFrame) {
        if (rolls.size() == 3) return true;
        if (rolls.size() == 2 && (rolls[0] + rolls[1] < 10)) return true;
        return false;
    } else {
        return isStrike() || rolls.size() == 2;
    }
}

const std::vector<int>& Frame::getRolls() const {
    return rolls;
}


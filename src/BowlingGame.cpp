#include "BowlingGame.hpp"
#include <stdexcept>

BowlingGame::BowlingGame() {
    frames.emplace_back(); // Start with first frame
}

void BowlingGame::validateRoll(int pins) const {
    if (pins < 0 || pins > 10)
        throw std::invalid_argument("Pins must be between 0 and 10.");
}

Frame& BowlingGame::currentFrame() {
    return frames.back();
}

void BowlingGame::roll(int pins) {
    validateRoll(pins);

    if (frames.size() < 10 && currentFrame().isComplete()) {
        if (frames.size() == 9)
            frames.emplace_back(true); // 10th frame
        else
            frames.emplace_back();     // normal frame
    }

    if (frames.size() > 10)
        throw std::out_of_range("Cannot roll after the 10th frame.");

    currentFrame().roll(pins);
}

int BowlingGame::score() const {
    int total = 0;
    for (size_t i = 0; i < frames.size(); ++i) {
        total += frames[i].score();

        if (i < 9) {
            if (frames[i].isStrike()) total += bonusForStrike(i);
            else if (frames[i].isSpare()) total += bonusForSpare(i);
        }
    }
    return total;
}

bool BowlingGame::isComplete() const {
    return frames.size() == 10 && frames.back().isComplete();
}

const std::vector<Frame>& BowlingGame::getFrames() const {
    return frames;
}

int BowlingGame::bonusForStrike(size_t index) const {
    int bonus = 0;
    size_t count = 0;

    for (size_t i = index + 1; i < frames.size() && count < 2; ++i) {
        for (int roll : frames[i].getRolls()) {
            bonus += roll;
            if (++count == 2) break;
        }
    }
    return bonus;
}

int BowlingGame::bonusForSpare(size_t index) const {
    if (index + 1 < frames.size() && !frames[index + 1].getRolls().empty())
        return frames[index + 1].getRolls()[0];
    return 0;
}

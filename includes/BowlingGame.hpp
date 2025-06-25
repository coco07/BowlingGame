#ifndef BOWLINGGAME_HPP
#define BOWLINGGAME_HPP

#include <vector>
#include "Frame.hpp"

class BowlingGame {
public:
    BowlingGame();
    void roll(int pins);
    int score() const;
    bool isComplete() const;
    const std::vector<Frame>& getFrames() const;

private:
    std::vector<Frame> frames;

    Frame& currentFrame();
    void validateRoll(int pins) const;
    int bonusForStrike(size_t index) const;
    int bonusForSpare(size_t index) const;
};

#endif


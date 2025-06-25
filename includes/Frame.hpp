#ifndef FRAME_HPP
#define FRAME_HPP

#include <vector>

class Frame {
public:
    Frame(bool isFinalFrame = false);
    void roll(int pins);
    int score() const;
    bool isStrike() const;
    bool isSpare() const;
    bool isComplete() const;
    const std::vector<int>& getRolls() const;

private:
    std::vector<int> rolls;
    bool finalFrame;
};

#endif


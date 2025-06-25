#include "Player.hpp"
#include <gtest/gtest.h>
#include <stdexcept>

TEST(BowlingGameTest, ScoreStartsAtZero) {
    Player player("Vijay");
    EXPECT_EQ(player.score(), 0);
}

TEST(BowlingGameTest, SingleRollAddsScore) {
    Player player("Vijay");
    player.roll(4);
    EXPECT_EQ(player.score(), 4);
}

TEST(BowlingGameTest, TwoRollsInFrame) {
    Player player("Vijay");
    player.roll(3);
    player.roll(6);
    EXPECT_EQ(player.score(), 9);
}

TEST(BowlingGameTest, InvalidNegativePinsThrows) {
    Player player("Vijay");
    EXPECT_THROW(player.roll(-2), std::invalid_argument);
}

TEST(BowlingGameTest, InvalidMoreThanTenPinsThrows) {
    Player player("Vijay");
    EXPECT_THROW(player.roll(11), std::invalid_argument);
}

TEST(BowlingGameTest, FrameCannotExceedTenPins) {
    Player player("Vijay");
    player.roll(6);
    EXPECT_THROW(player.roll(5), std::invalid_argument);
}

TEST(BowlingGameTest, SpareGivesNextRollBonus) {
    Player player("Vijay");
    player.roll(5);
    player.roll(5); // spare
    player.roll(4);
    for (int i = 0; i < 17; ++i) player.roll(0);
    EXPECT_EQ(player.score(), 18);
}

TEST(BowlingGameTest, StrikeGivesTwoRollBonus) {
    Player player("Vijay");
    player.roll(10); // strike
    player.roll(3);
    player.roll(4);
    for (int i = 0; i < 16; ++i) player.roll(0);
    EXPECT_EQ(player.score(), 24);
}

TEST(BowlingGameTest, TwoConsecutiveStrikes) {
    Player player("Vijay");
    player.roll(10);
    player.roll(10);
    player.roll(5);
    player.roll(2);
    for (int i = 0; i < 14; ++i) player.roll(0);
    EXPECT_EQ(player.score(), 10 + 10 + 5 + 10 + 5 + 2 + 5 + 2);
}

TEST(BowlingGameTest, PerfectGameReturns300RawScoreInNewRules) {
    Player player("Vijay");
    for (int i = 0; i < 9; ++i) player.roll(10);
    player.roll(10); // 10th frame
    player.roll(10);
    player.roll(10);
    EXPECT_EQ(player.score(), 300); // No bonus scoring beyond 10th frame, but all raw pins count
}

TEST(BowlingGameTest, SpareIn10thAllowsOneMoreRoll) {
    Player player("Vijay");
    for (int i = 0; i < 9; ++i) {
        player.roll(3);
        player.roll(4);
    }
    player.roll(5);
    player.roll(5); // Spare in 10th
    player.roll(7);
    EXPECT_EQ(player.score(), 9 * 7 + 17);
}

TEST(BowlingGameTest, StrikeIn10thAllowsTwoMoreRolls) {
    Player player("Vijay");
    for (int i = 0; i < 9; ++i) {
        player.roll(4);
        player.roll(4);
    }
    player.roll(10);  // Strike
    player.roll(7);   // Bonus 1
    player.roll(2);   // Bonus 2
    EXPECT_EQ(player.score(), 9 * 8 + 10 + 7 + 2);
}

TEST(BowlingGameTest, NoSpareOrStrikeIn10thDisallows3rdRoll) {
    Player player("Vijay");
    for (int i = 0; i < 9; ++i) {
        player.roll(3);
        player.roll(4);
    }
    player.roll(5);
    player.roll(3); // 10th frame, no spare
    EXPECT_THROW(player.roll(2), std::out_of_range);
}

TEST(BowlingGameTest, CannotRollAfterGameIsComplete) {
    Player player("Vijay");
    for (int i = 0; i < 9; ++i)
        player.roll(4), player.roll(4);

    player.roll(10); // strike in 10th
    player.roll(10);
    player.roll(10); // this is the 3rd roll of final frame

    EXPECT_THROW(player.roll(1), std::out_of_range);
}

TEST(BowlingGameTest, CannotExceedThreeRollsIn10thEvenIfAllStrikes) {
    Player player("Vijay");
    for (int i = 0; i < 9; ++i)
        player.roll(10);

    player.roll(10); // 10th frame
    player.roll(10);
    player.roll(10);

    EXPECT_THROW(player.roll(10), std::out_of_range);
}

TEST(BowlingGameTest, Frame10_StrikeThenTwoRolls10PinsAllowed) {
    Player player("Vijay");
    for (int i = 0; i < 9; ++i)
        player.roll(1), player.roll(1);

    player.roll(10);
    player.roll(10);
    player.roll(10);
    EXPECT_EQ(player.score(), 9 * 2 + 30);
}

TEST(BowlingGameTest, Frame10_SpareThenOneBonusRollAllowed) {
    Player player("Vijay");
    for (int i = 0; i < 9; ++i)
        player.roll(1), player.roll(1);

    player.roll(4);
    player.roll(6); // spare
    player.roll(8); // one bonus
    EXPECT_THROW(player.roll(1), std::out_of_range);
}

TEST(BowlingGameTest, ScoreCorrectlyWithAllZeros) {
    Player player("Vijay");
    for (int i = 0; i < 20; ++i)
        player.roll(0);
    EXPECT_EQ(player.score(), 0);
}

TEST(BowlingGameTest, ScoreCorrectlyWithAllFours) {
    Player player("Vijay");
    for (int i = 0; i < 20; ++i)
        player.roll(4);
    EXPECT_EQ(player.score(), 80);
}

TEST(BowlingGameTest, InvalidRollInFinalFrame) {
    Player player("Vijay");
    for (int i = 0; i < 9; ++i)
        player.roll(4), player.roll(4);

    player.roll(6);
    player.roll(3); // no spare or strike
    EXPECT_THROW(player.roll(1), std::out_of_range);
}


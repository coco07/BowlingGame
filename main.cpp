#include "Player.hpp"
#include <iostream>
#include <limits>

int main() {
    std::string playerName;

    std::cout << "Welcome to the Bowling Game.\n";
    std::cout << "Enter player name: ";
    std::getline(std::cin, playerName);

    if (playerName.empty()) {
        std::cerr << "Name cannot be empty. Exiting.\n";
        return 1;
    }

    Player player(playerName);

    std::cout << "Hello, " << player.getName() << ". Let's begin.\n";
    std::cout << "Enter pins knocked down per roll (0-10):\n";

    int frameNumber = 0;
    int rollInFrame = 0;
    bool newFrame = true;

    while (true) {
        // Get current frame info
        const auto& frames = player.getFrames();

        // Only print new frame header when needed
        if (newFrame) {
            ++frameNumber;
            rollInFrame = 1;
            std::cout << "Frame #" << frameNumber << "\n";
            newFrame = false;
        }

        std::cout << "  Roll #" << rollInFrame << ": ";

        int pins;
        std::cin >> pins;

        if (std::cin.fail()) {
            std::cin.clear(); // reset input stream
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid input. Enter a number between 0 and 10.\n";
            continue;
        }

        try {
            player.roll(pins);

            // Check if we need to move to the next frame
            const auto& updatedFrames = player.getFrames();
            const auto& currentFrame = updatedFrames[frameNumber - 1];

            ++rollInFrame;

            if (currentFrame.isComplete()) {
                newFrame = true;
            }

            if (player.isGameComplete()) {
                std::cout << "Game complete.\n";
                break;
            }

        } catch (const std::out_of_range& e) {
            std::cout << "Game over: " << e.what() << "\n";
            break;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid roll: " << e.what() << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Unexpected error: " << e.what() << "\n";
        }
    }

    std::cout << "\nFinal score for " << player.getName() << ": " << player.score() << "\n";
    return 0;
}


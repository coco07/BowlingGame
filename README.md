# BowlingGame
A modular, object-oriented C++ console application that simulates a standard 10-frame bowling game for a single player. Designed to demonstrate clean class architecture, robust exception handling, and comprehensive unit testing using Google Test. It faithfully implements bowling rules including strike/spare logic, bonus rolls, and final frame edge cases.

## UML Class Diagram
![Image Not Found](https://github.com/coco07/BowlingGame/blob/main/BowlingGameUML.png?raw=true)

## Prerequisites
1. CMake >= 3.10
2. C++ compiler
3. GoogleTest

## Build & Run
```
git clone https://github.com/coco07/BowlingGame.git
cd BowlingGame
mkdir build
cd build
cmake ..
make
```

### Run the Unit Tests
`./test`

### Run the Console App
`./main`

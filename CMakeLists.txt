cmake_minimum_required(VERSION 3.10)
project(BowlingGame)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/includes)

# Source files
set(SOURCES
    src/Frame.cpp
    src/BowlingGame.cpp
    src/Player.cpp
)

# Main app
add_executable(main main.cpp ${SOURCES})

# GTest app
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test tests/BowlingGameTest.cpp ${SOURCES})
target_link_libraries(test ${GTEST_LIBRARIES} gtest_main pthread)

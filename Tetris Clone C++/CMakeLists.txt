cmake_minimum_required (VERSION 2.6)
ADD_DEFINITIONS(-std=c++14 -Wall -Winit-self -Wextra -Weffc++ -pedantic -Wredundant-decls -Wcast-align -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Winvalid-pch -flto -Wodr -Wformat=2 -Wmissing-format-attribute -Wformat-nonliteral -Werror)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

project(Tetris)
add_executable(Tetris main.cpp Monomino.cpp TetrisPiece.cpp GridController.cpp)
target_link_libraries(Tetris -lsfml-graphics -lsfml-window -lsfml-system)
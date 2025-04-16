cmake_minimum_required(VERSION 3.10)
project(Chess)

set(CMAKE_CXX_STANDARD 11)

add_executable(Chess
    src/main.cpp
    src/Board.cpp
    src/Chess.cpp
    src/Bishop.cpp
    src/King.cpp
    src/Knight.cpp
    src/Pawn.cpp
    src/Piece.cpp
    src/Queen.cpp
    src/Rook.cpp
)

target_include_directories(Chess PRIVATE include)

//
// Created by leth1 on 7/12/2024.
//

#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H
#include <sstream>
#include <string>

struct Move {
    int fromRow, fromCol;   // Starting position (row, column)
    int toRow, toCol;       // Ending position (row, column)
    char capturedPiece;     // Captured piece ('-' if none)
    int moveScore;          // Score assigned to the move

    // Constructor for convenience
    Move(int fromR, int fromC, int toR, int toC, char captured, int score)
            : fromRow(fromR), fromCol(fromC), toRow(toR), toCol(toC), capturedPiece(captured), moveScore(score) {}
};
#endif //CHESS_MOVE_H
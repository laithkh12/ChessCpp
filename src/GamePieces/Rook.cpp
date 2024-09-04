#include "GamePieces/Rook.h"
#include "Factory.h"
#include "Location.h"
#include <iostream>
#include <vector>

bool Rook::m_registerit = GamePiece::registerPiece<Rook>('R', 'r');
Rook::Rook() : GamePiece(true){}

Rook::Rook(bool isWhite) :
        GamePiece(isWhite)
{
}

bool Rook::isLegalMove(const Position& source, const Position& dest, bool /*OpponentDest*/) const
{
    // move only in straight lines
    return source.x == dest.x || source.y == dest.y;
}

std::vector<Location> Rook::stepHorizontalRookWhite(char in0, char in1, unsigned char board[21][21]) {
    std::vector<Location> possibleMoves;

    // Convert board position to internal row and column indices
    int col = in1 - 'a'; // Convert column 'a' to 0, 'b' to 1, etc.
    int row = in0 - '1'; // Convert row '1' to 0, '2' to 1, etc.

    // Check moves to the right
    for (int c = col + 1; c < 21; ++c) {
        if (board[3 + c * 2][3 + row * 2] == ' ') {
            possibleMoves.push_back({ row, c });
        } else {
            break; // Stop if we encounter a piece or edge of the board
        }
    }

    // Check moves to the left
    for (int c = col - 1; c >= 0; --c) {
        if (board[3 + c * 2][3 + row * 2] == ' ') {
            possibleMoves.push_back({ row, c });
        } else {
            break; // Stop if we encounter a piece or edge of the board
        }
    }

    return possibleMoves;
}



std::vector<Location> Rook::stepVerticalRookWhite(char in0, char in1, unsigned char board[21][21]) {
    std::vector<Location> possibleMoves;

    // Convert board position to internal row and column indices
    int col = in1 - 'a'; // Convert column 'a' to 0, 'b' to 1, etc.
    int row = in0 - '1'; // Convert row '1' to 0, '2' to 1, etc.

    // Check moves upwards
    for (int r = row + 1; r < 21; ++r) {
        if (board[3 + col * 2][3 + r * 2] == ' ') {
            possibleMoves.push_back({ r, col });
        } else {
            break; // Stop if we encounter a piece or edge of the board
        }
    }

    // Check moves downwards
    for (int r = row - 1; r >= 0; --r) {
        if (board[3 + col * 2][3 + r * 2] == ' ') {
            possibleMoves.push_back({ r, col });
        } else {
            break; // Stop if we encounter a piece or edge of the board
        }
    }

    return possibleMoves;
}

std::vector<Location> Rook::stepHorizontalRookBlack(char in0, char in1, unsigned char board[21][21]) {
    std::vector<Location> possibleMoves;

    // Convert board position to internal row and column indices
    int col = in1 - 'a'; // Convert column 'a' to 0, 'b' to 1, etc.
    int row = in0 - '1'; // Convert row '1' to 0, '2' to 1, etc.

    // Check moves to the right
    for (int c = col + 1; c < 21; ++c) {
        if (board[3 + c * 2][3 + row * 2] == ' ') {
            possibleMoves.push_back({ row, c });
        } else {
            break; // Stop if we encounter a piece or edge of the board
        }
    }

    // Check moves to the left
    for (int c = col - 1; c >= 0; --c) {
        if (board[3 + c * 2][3 + row * 2] == ' ') {
            possibleMoves.push_back({ row, c });
        } else {
            break; // Stop if we encounter a piece or edge of the board
        }
    }

    return possibleMoves;
}

std::vector<Location> Rook::stepVerticalRookBlack(char in0, char in1, unsigned char board[21][21]) {
    std::vector<Location> possibleMoves;

    // Convert board position to internal row and column indices
    int col = in1 - 'a'; // Convert column 'a' to 0, 'b' to 1, etc.
    int row = in0 - '1'; // Convert row '1' to 0, '2' to 1, etc.

    // Check moves upwards
    for (int r = row + 1; r < 21; ++r) {
        if (board[3 + col * 2][3 + r * 2] == ' ') {
            possibleMoves.push_back({ r, col });
        } else {
            break; // Stop if we encounter a piece or edge of the board
        }
    }

    // Check moves downwards
    for (int r = row - 1; r >= 0; --r) {
        if (board[3 + col * 2][3 + r * 2] == ' ') {
            possibleMoves.push_back({ r, col });
        } else {
            break; // Stop if we encounter a piece or edge of the board
        }
    }

    return possibleMoves;
}
#include <vector>
#include "GamePieces/Queen.h"
#include "Factory.h"
#include "Location.h"

bool Queen::m_registerit = GamePiece::registerPiece<Queen>('Q', 'q');

Queen::Queen(bool isWhite) :
        GamePiece(isWhite)
{
}

bool Queen::isLegalMove(const Position& source, const Position& dest, bool /*OpponentDest*/) const
{
    // move stright or diagonally
    return (source.x == dest.x || source.y == dest.y) ||
           (abs(dest.x - source.x) == abs(dest.y - source.y));
}

Queen::Queen()  : GamePiece(true) {

}
std::vector<Location> Queen::stepHorizontalQueenWhite(char in0, char in1, unsigned char board[21][21]) {
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



std::vector<Location> Queen::stepVerticalQueenWhite(char in0, char in1, unsigned char board[21][21]) {
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

std::vector<Location> Queen::stepHorizontalQueenBlack(char in0, char in1, unsigned char board[21][21]) {
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

std::vector<Location> Queen::stepVerticalQueenBlack(char in0, char in1, unsigned char board[21][21]) {
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

std::vector<Location> Queen::stepDiagonalQueenWhite(char in0, char in1, unsigned char board[21][21]) {
    std::vector<Location> possibleMoves;
    int col = in1 - 'a';
    int row = in0 - '1';

    // Check diagonal moves
    // Top-right
    for (int r = row + 1, c = col + 1; r < 21 && c < 21; ++r, ++c) {
        if (board[3 + c * 2][3 + r * 2] == ' ') {
            possibleMoves.push_back({ r, c });
        } else {
            break;
        }
    }
    // Top-left
    for (int r = row + 1, c = col - 1; r < 21 && c >= 0; ++r, --c) {
        if (board[3 + c * 2][3 + r * 2] == ' ') {
            possibleMoves.push_back({ r, c });
        } else {
            break;
        }
    }
    // Bottom-right
    for (int r = row - 1, c = col + 1; r >= 0 && c < 21; --r, ++c) {
        if (board[3 + c * 2][3 + r * 2] == ' ') {
            possibleMoves.push_back({ r, c });
        } else {
            break;
        }
    }
    // Bottom-left
    for (int r = row - 1, c = col - 1; r >= 0 && c >= 0; --r, --c) {
        if (board[3 + c * 2][3 + r * 2] == ' ') {
            possibleMoves.push_back({ r, c });
        } else {
            break;
        }
    }

    return possibleMoves;
}

std::vector<Location> Queen::stepDiagonalQueenBlack(char in0, char in1, unsigned char board[21][21]) {
    std::vector<Location> possibleMoves;
    int col = in1 - 'a';
    int row = in0 - '1';

    // Check diagonal moves
    // Top-right
    for (int r = row + 1, c = col + 1; r < 21 && c < 21; ++r, ++c) {
        if (board[3 + c * 2][3 + r * 2] == ' ') {
            possibleMoves.push_back({ r, c });
        } else {
            break;
        }
    }
    // Top-left
    for (int r = row + 1, c = col - 1; r < 21 && c >= 0; ++r, --c) {
        if (board[3 + c * 2][3 + r * 2] == ' ') {
            possibleMoves.push_back({ r, c });
        } else {
            break;
        }
    }
    // Bottom-right
    for (int r = row - 1, c = col + 1; r >= 0 && c < 21; --r, ++c) {
        if (board[3 + c * 2][3 + r * 2] == ' ') {
            possibleMoves.push_back({ r, c });
        } else {
            break;
        }
    }
    // Bottom-left
    for (int r = row - 1, c = col - 1; r >= 0 && c >= 0; --r, --c) {
        if (board[3 + c * 2][3 + r * 2] == ' ') {
            possibleMoves.push_back({ r, c });
        } else {
            break;
        }
    }

    return possibleMoves;
}
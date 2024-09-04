#include "GamePieces/Bishop.h"
#include "Factory.h"

bool Bishop::m_registerit = GamePiece::registerPiece<Bishop>('B', 'b');

Bishop::Bishop(bool isWhite) :
        GamePiece(isWhite)
{
}

bool Bishop::isLegalMove(const Position& source, const Position& dest, bool /*OpponentDest*/) const
{
    //move only diagonally
    return abs(dest.x - source.x) == abs(dest.y - source.y);
}

Bishop::Bishop() : GamePiece(true) {

}

std::vector<Location> Bishop::stepDiagonalBishopWhite(char in0, char in1, unsigned char board[21][21]) {
    std::vector<Location> possibleMoves;

    // Convert board position to internal row and column indices
    int col = in1 - 'a'; // Convert column 'a' to 0, 'b' to 1, etc.
    int row = in0 - '1'; // Convert row '1' to 0, '2' to 1, etc.

    // Check moves diagonally up-right
    for (int r = row + 1, c = col + 1; r < 21 && c < 21; ++r, ++c) {
        if (board[3 + c * 2][3 + r * 2] == ' ') {
            possibleMoves.push_back({ r, c });
        } else {
            break; // Stop if we encounter a piece or edge of the board
        }
    }

    // Check moves diagonally up-left
    for (int r = row + 1, c = col - 1; r < 21 && c >= 0; ++r, --c) {
        if (board[3 + c * 2][3 + r * 2] == ' ') {
            possibleMoves.push_back({ r, c });
        } else {
            break; // Stop if we encounter a piece or edge of the board
        }
    }

    // Check moves diagonally down-right
    for (int r = row - 1, c = col + 1; r >= 0 && c < 21; --r, ++c) {
        if (board[3 + c * 2][3 + r * 2] == ' ') {
            possibleMoves.push_back({ r, c });
        } else {
            break; // Stop if we encounter a piece or edge of the board
        }
    }

    // Check moves diagonally down-left
    for (int r = row - 1, c = col - 1; r >= 0 && c >= 0; --r, --c) {
        if (board[3 + c * 2][3 + r * 2] == ' ') {
            possibleMoves.push_back({ r, c });
        } else {
            break; // Stop if we encounter a piece or edge of the board
        }
    }

    return possibleMoves;
}

std::vector<Location> Bishop::stepDiagonalBishopBlack(char in0, char in1, unsigned char board[21][21]) {
    std::vector<Location> possibleMoves;

    // Convert board position to internal row and column indices
    int col = in1 - 'a'; // Convert column 'a' to 0, 'b' to 1, etc.
    int row = in0 - '1'; // Convert row '1' to 0, '2' to 1, etc.

    // Check moves diagonally up-right
    for (int r = row + 1, c = col + 1; r < 21 && c < 21; ++r, ++c) {
        if (board[3 + c * 2][3 + r * 2] == ' ') {
            possibleMoves.push_back({ r, c });
        } else {
            break; // Stop if we encounter a piece or edge of the board
        }
    }

    // Check moves diagonally up-left
    for (int r = row + 1, c = col - 1; r < 21 && c >= 0; ++r, --c) {
        if (board[3 + c * 2][3 + r * 2] == ' ') {
            possibleMoves.push_back({ r, c });
        } else {
            break; // Stop if we encounter a piece or edge of the board
        }
    }

    // Check moves diagonally down-right
    for (int r = row - 1, c = col + 1; r >= 0 && c < 21; --r, ++c) {
        if (board[3 + c * 2][3 + r * 2] == ' ') {
            possibleMoves.push_back({ r, c });
        } else {
            break; // Stop if we encounter a piece or edge of the board
        }
    }

    // Check moves diagonally down-left
    for (int r = row - 1, c = col - 1; r >= 0 && c >= 0; --r, --c) {
        if (board[3 + c * 2][3 + r * 2] == ' ') {
            possibleMoves.push_back({ r, c });
        } else {
            break; // Stop if we encounter a piece or edge of the board
        }
    }

    return possibleMoves;
}
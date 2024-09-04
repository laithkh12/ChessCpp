#include "GamePieces/King.h"
#include "Factory.h"

bool King::m_registerit = GamePiece::registerPiece<King>('K', 'k');

King::King(bool isWhite) :
        GamePiece(isWhite)
{
}

bool King::isLegalMove(const Position& source, const Position& dest, bool /*OpponentDest*/) const
{
    // move only one spot in any direction
    return abs(dest.x - source.x) <= 1 && abs(dest.y - source.y) <= 1;
}

King::King() : GamePiece(true){

}
std::vector<Location> King::stepKingWhite(char in0, char in1, unsigned char board[21][21]) {
    std::vector<Location> possibleMoves;
    int col = in1 - 'a'; // Convert column 'a' to 0, 'b' to 1, etc.
    int row = in0 - '1'; // Convert row '1' to 0, '2' to 1, etc.

    // Add logic for calculating the white king's possible moves
    // Example:
    int directions[8][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    for (const auto& dir : directions) {
        int newRow = row + dir[0];
        int newCol = col + dir[1];
        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
            if (board[3 + newCol * 2][3 + newRow * 2] == ' ' || islower(board[3 + newCol * 2][3 + newRow * 2])) {
                possibleMoves.push_back({newRow, newCol});
            }
        }
    }

    return possibleMoves;
}

std::vector<Location> King::stepKingBlack(char in0, char in1, unsigned char board[21][21]) {
    std::vector<Location> possibleMoves;
    int col = in1 - 'a'; // Convert column 'a' to 0, 'b' to 1, etc.
    int row = in0 - '1'; // Convert row '1' to 0, '2' to 1, etc.

    // Add logic for calculating the black king's possible moves
    // Example:
    int directions[8][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    for (const auto& dir : directions) {
        int newRow = row + dir[0];
        int newCol = col + dir[1];
        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
            if (board[3 + newCol * 2][3 + newRow * 2] == ' ' || isupper(board[3 + newCol * 2][3 + newRow * 2])) {
                possibleMoves.push_back({newRow, newCol});
            }
        }
    }

    return possibleMoves;
}
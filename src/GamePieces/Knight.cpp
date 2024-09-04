#include "GamePieces/Knight.h"
#include "Factory.h"

bool Knight::m_registerit = GamePiece::registerPiece<Knight>('N', 'n');

Knight::Knight(bool isWhite) :
        GamePiece(isWhite)
{
}

bool Knight::isLegalMove(const Position& source, const Position& dest, bool /*OpponentDest*/) const
{
    // move two spots in one direction and one spot in the other direction
    return (abs(dest.x - source.x) == 2 && abs(dest.y - source.y) == 1) ||
           (abs(dest.x - source.x) == 1 && abs(dest.y - source.y) == 2);
}

Knight::Knight(): GamePiece(true) {

}
std::vector<Location> Knight::stepKnightWhite(char in0, char in1, unsigned char board[21][21]) {
    std::vector<Location> possibleMoves;

    // Convert board position to internal row and column indices
    int col = in1 - 'a';
    int row = in0 - '1';

    // Possible knight moves relative to its position
    std::vector<std::pair<int, int>> knightMoves = {
            {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
            {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
    };

    for (auto& move : knightMoves) {
        int new_row = row + move.first;
        int new_col = col + move.second;

        if (new_row >= 0 && new_row < 8 && new_col >= 0 && new_col < 8 &&
            board[3 + new_col * 2][3 + new_row * 2] == ' ') {
            possibleMoves.push_back({ new_row, new_col });
        }
    }

    return possibleMoves;
}

std::vector<Location> Knight::stepKnightBlack(char in0, char in1, unsigned char board[21][21]) {
    std::vector<Location> possibleMoves;

    // Convert board position to internal row and column indices
    int col = in1 - 'a';
    int row = in0 - '1';

    // Possible knight moves relative to its position
    std::vector<std::pair<int, int>> knightMoves = {
            {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
            {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
    };

    for (auto& move : knightMoves) {
        int new_row = row + move.first;
        int new_col = col + move.second;

        if (new_row >= 0 && new_row < 8 && new_col >= 0 && new_col < 8 &&
            board[3 + new_col * 2][3 + new_row * 2] == ' ') {
            possibleMoves.push_back({ new_row, new_col });
        }
    }

    return possibleMoves;
}

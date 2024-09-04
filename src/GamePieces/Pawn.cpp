#include "GamePieces/Pawn.h"
#include "Factory.h"
#include "ChessBoard.h"
#include "Location.h"

bool Pawn::m_registerit = GamePiece::registerPiece<Pawn>('P', 'p');

Pawn::Pawn(bool isWhite) :
        GamePiece(isWhite)
{
}

bool Pawn::isLegalMove(const Position& source, const Position& dest, bool OpponentDest) const
{
    int direction = (this->getColor() == WHITE) ? 1 : -1; //pawn's direction
    int rowDiff = dest.x - source.x;
    int colDiff = dest.y - source.y;

    // move forward one step or two steps if it's the first move
    if (!OpponentDest && colDiff == 0 && (rowDiff == direction ||
                                          rowDiff == 2 * direction && m_isFirstMove)) {
        m_isFirstMove = false;
        return true;
    }
        // can take it's opponent's piece one step forward diagonally
    else if (OpponentDest && abs(colDiff) == 1 &&
             rowDiff == direction) {
        return true;
    }

    return false;
}

std::vector<Location> Pawn::stepForwardWhitePawn(char in0, char in1, unsigned char board[21][21])  {
    std::vector<Location> possibleMoves;

    // Convert board position to internal row and column indices
    int col = in1 - 'a' + 1; // Convert column 'a' to 1, 'b' to 2, etc.
    int row = in0 - '1';     // Convert row '1' to 0, '2' to 1, etc.

    // Check one step forward
    if (board[3 + col * 2][3 + row * 2] == ' ') {
        possibleMoves.push_back({row , col});
    }

    return possibleMoves;
}


Pawn::Pawn() : GamePiece(true) {

}

std::vector<Location> Pawn::stepForwardBlackPawn(char in0, char in1, unsigned char board[21][21]) {
    std::vector<Location> possibleMoves;

    // Convert board position to internal row and column indices
    int col = in1 - 'a' - 1; // Convert column 'a' to 1, 'b' to 2, etc.
    int row = in0 - '1';     // Convert row '1' to 0, '2' to 1, etc.

    // Check one step forward
    if (board[3 + col * 2][3 + row * 2] == ' ') {
        possibleMoves.push_back({row , col});
    }

    return possibleMoves;

}




#pragma once
#include "GamePieces/GamePiece.h"
#include "macros.h"
#include "Location.h"
#include <optional>
#include <vector>

class Pawn : public GamePiece {

public:
    Pawn(bool isWhite);
    bool isLegalMove(const Position& source, const Position& dest, bool OpponentDest) const override;
    Pawn();
    std::vector<Location> stepForwardWhitePawn(char row, char col, unsigned char board[21][21]);
    std::vector<Location> stepForwardBlackPawn(char in0, char in1, unsigned char[21][21]);

private:
    static bool m_registerit;
    bool mutable m_isFirstMove = true;



};
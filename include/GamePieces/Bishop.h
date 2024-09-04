#pragma once

#include <vector>
#include "GamePieces/GamePiece.h"
#include "macros.h"
#include "Location.h"

class Bishop : public GamePiece {

public:
    Bishop(bool isWhite);
    bool isLegalMove(const Position& source, const Position& dest, bool OpponentDest) const override;
    Bishop();
    std::vector<Location> stepDiagonalBishopWhite(char in0, char in1, unsigned char board[21][21]);
    std::vector<Location> stepDiagonalBishopBlack(char in0, char in1, unsigned char board[21][21]);

private:
    static bool m_registerit;
};
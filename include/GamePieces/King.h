#pragma once

#include <vector>
#include "GamePieces/GamePiece.h"
#include "macros.h"
#include "Location.h"

class King : public GamePiece {

public:
    King(bool isWhite);
    bool isLegalMove(const Position& source, const Position& dest, bool OpponentDest) const override;
    King();
    std::vector<Location> stepKingWhite(char in0, char in1, unsigned char board[21][21]);
    std::vector<Location> stepKingBlack(char in0, char in1, unsigned char board[21][21]);

private:
    static bool m_registerit;
};
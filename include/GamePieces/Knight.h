#pragma once
#include "GamePieces/GamePiece.h"
#include "macros.h"
#include <iostream>
#include "Location.h"
#include <vector>
class Knight : public GamePiece {

public:
    Knight(bool isWhite);
    bool isLegalMove(const Position& source, const Position& dest, bool OpponentDest) const override;
    Knight();
    std::vector<Location> stepKnightWhite(char in0, char in1, unsigned char board[21][21]);
    std::vector<Location> stepKnightBlack(char in0, char in1, unsigned char board[21][21]);

private:
    static bool m_registerit;
};
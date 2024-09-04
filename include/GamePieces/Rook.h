#pragma once

#include <vector>
#include "GamePieces/GamePiece.h"
#include "macros.h"
#include "Location.h"

class Rook : public GamePiece {

public:
    Rook(bool isWhite);
    bool isLegalMove(const Position& source, const Position& dest, bool OpponentDest) const override;
    Rook();
    std::vector<Location> stepHorizontalRookWhite(char in0, char in1, unsigned char[21][21]);
    std::vector<Location> stepHorizontalRookBlack(char in0, char in1, unsigned char[21][21]);
    std::vector<Location> stepVerticalRookWhite(char in0, char in1, unsigned char[21][21]);
    std::vector<Location> stepVerticalRookBlack(char in0, char in1, unsigned char[21][21]);
private:
    static bool m_registerit;



};
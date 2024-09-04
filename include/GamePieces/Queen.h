#pragma once
#include "GamePieces/GamePiece.h"
#include "macros.h"
#include "Location.h"

class Queen : public GamePiece {

public:
    Queen(bool isWhite);
    bool isLegalMove(const Position& source, const Position& dest, bool OpponentDest) const override;
    std::vector<Location> stepHorizontalQueenWhite(char in0, char in1, unsigned char[21][21]);
    std::vector<Location> stepVerticalQueenWhite(char in0, char in1, unsigned char[21][21]);
    std::vector<Location> stepHorizontalQueenBlack(char in0, char in1, unsigned char[21][21]);
    std::vector<Location> stepVerticalQueenBlack(char in0, char in1, unsigned char[21][21]);
    std::vector<Location> stepDiagonalQueenWhite(char in0, char in1, unsigned char[21][21]);
    std::vector<Location> stepDiagonalQueenBlack(char in0, char in1, unsigned char[21][21]);

    Queen();
private:
    static bool m_registerit;


};
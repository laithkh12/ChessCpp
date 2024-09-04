#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include "Location.h"
#include "PriorityQueue.h"
#include "GamePieces/GamePiece.h"
#include "GamePieces/Pawn.h"
#include "GamePieces/Rook.h"
#include "GamePieces/Knight.h"
#include "GamePieces/Bishop.h"
#include "GamePieces/Queen.h"
#include "GamePieces/King.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

const int _SIZE = 21;


// Define Move structure
struct Move {
    Position from;
    Position to;

    Move(Position f, Position t) : from(f), to(t) {}
};
class Chess {
    unsigned char m_board[_SIZE][_SIZE] = { 0 };
    bool m_turn = true;
    string m_boardString;
    string m_input;
    string m_msg = "\n";
    string m_errorMsg = "\n";
    int m_codeResponse;
    PriorityQueue moveQueue;

    void clear() const;
    void setFrames();
    void setPieces();
    void show() const;
    void displayBoard() const;
    void showAskInput() const;
    bool isSame() const;
    bool isValid() const;
    bool isExit() const;
    void excute();
    void doTurn();
    std::vector<std::string> m_inputsToCheck;
    size_t m_inputsToCheckIndex;
public:
    Chess(const string& start = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr");
    Chess(const Chess&)=delete;
    Chess& operator=(const Chess&) = delete;
    string getInput();
    void setCodeResponse(int codeResponse);

    void executeCastling();

    void promotePawn(Location loc);
    std::chrono::milliseconds setInputsToCheck(const std::vector<std::string>& inputs, int processNum);


    std::vector<Location> getPieceMoves();
    std::vector<Location> calculateMoves(char piece, char rand_row, char rand_col, unsigned char board[21][21]);

    bool isValidMove(const Location &move);
};
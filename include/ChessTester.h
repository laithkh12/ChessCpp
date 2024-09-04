//
// Created by leth1 on 7/16/2024.
//

#ifndef CHESS_CHESSTESTER_H
#define CHESS_CHESSTESTER_H
#include <iostream>
#include <vector>
#include <chrono>
#include "Chess.h" // Assuming Chess class is defined in Chess.h

class ChessTester {
public:
    void runTest(int numProcesses, const std::vector<std::string>& inputsToCheck);
};
#endif //CHESS_CHESSTESTER_H
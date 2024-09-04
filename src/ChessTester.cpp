//
// Created by leth1 on 7/16/2024.
//
#include "../include/ChessTester.h"
void ChessTester::runTest(int numProcesses, const std::vector<std::string>& inputsToCheck) {
    std::cout << "Running test with " << numProcesses << " processes..." << std::endl;

    // Create Chess instance with initial board setup
    std::string initialBoard = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
    Chess chess(initialBoard);

    // Measure time and store result of setInputsToCheck
    auto elapsed = chess.setInputsToCheck(inputsToCheck, numProcesses);

    std::cout << "Test with " << numProcesses << " processes completed in " << elapsed.count() << " ms." << std::endl;
}
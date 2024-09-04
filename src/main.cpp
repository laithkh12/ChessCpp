// Chess
#include "Chess.h"
#include "ChessBoard.h"
#include "ChessTester.h"
#include <chrono>
#include <vector>
#include <iostream>
using namespace std;


int main()
{
    string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
    //string board = "##########K################p#k############R#############r#r#####";
    std::vector<std::string> inputsToCheck = {"b5d5","g6f6","a5b5","g8e8","b5d7","e8d8","d7f7"};
//	Chess a(board);
//	ChessBoard chessBoard(board);
//	int codeResponse = 0;
//	string res = a.getInput();
//	while (res != "exit")
//	{
//		/*
//		codeResponse value :
//		Illegal movements :
//		11 - there is not piece at the source
//		12 - the piece in the source is piece of your opponent
//		13 - there one of your pieces at the destination
//		21 - illegal movement of that piece
//		31 - this movement will cause you checkmate
//
//		legal movements :
//		41 - the last movement was legal and cause check
//		42 - the last movement was legal, next turn
//		*/
//
//		/**/
//		{ // put your code here instead that code
//			codeResponse = chessBoard.execute(res);
//		}
//		/**/
//
//		a.setCodeResponse(codeResponse);
//		res = a.getInput();
//	}

    ChessTester tester;
    tester.runTest(1, inputsToCheck);
    tester.runTest(2, inputsToCheck);
    tester.runTest(4, inputsToCheck);
    tester.runTest(8, inputsToCheck);
    cout << endl << "Exiting " << endl;
    return 0;
}
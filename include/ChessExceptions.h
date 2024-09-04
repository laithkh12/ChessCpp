//
// Created by leth1 on 7/12/2024.
//

#ifndef CHESS_CHESSEXCEPTIONS_H
#define CHESS_CHESSEXCEPTIONS_H
#include <exception>
#include <string>

class ChessException : public std::exception {
public:
    explicit ChessException(const std::string& message) : msg_(message) {}
    virtual const char* what() const noexcept override {
        return msg_.c_str();
    }
private:
    std::string msg_;
};

class InvalidMoveException : public ChessException {
public:
    explicit InvalidMoveException(const std::string& message) : ChessException(message) {}
};

class CheckmateException : public ChessException {
public:
    explicit CheckmateException(const std::string& message) : ChessException(message) {}
};
#endif //CHESS_CHESSEXCEPTIONS_H
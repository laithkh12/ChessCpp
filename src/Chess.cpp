#include <future>
#include "Chess.h"
#include "../include/ChessExceptions.h"
#include "../include/GamePieces/GamePiece.h"
#include "Location.h"
#include "GamePieces/Pawn.h"
std::mutex inputMutex;
// clear the screen "cls"
void Chess::clear() const
{
    COORD topLeft = { 0, 0 };
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
            console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    FillConsoleOutputAttribute(
            console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
            screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    SetConsoleCursorPosition(console, topLeft);
}
// create the GUI - ASCII art
void Chess::setFrames()
{
    // set all to ' ' (space bar ascii value 32) instead of 0
    {
        for (size_t row = 0; row < _SIZE; ++row)
            for (size_t col = 0; col < _SIZE; ++col)
                m_board[row][col] = 32;
    }
    // set out frame
    {
        m_board[0][0] = 201;  m_board[0][20] = 187;
        m_board[20][0] = 200; m_board[20][20] = 188;

        for (size_t i = 1; i < 20; ++i)
        {
            m_board[0][i] = 205;
            m_board[20][i] = 205;
            m_board[i][0] = 186;
            m_board[i][20] = 186;
        }
    }

    // set in side frame
    {
        m_board[2][2] = 218;  m_board[2][18] = 191;
        m_board[18][2] = 192; m_board[18][18] = 217;

        for (size_t i = 4; i < 17; i += 2)
        {
            m_board[2][i] = 194;
            m_board[18][i] = 193;
            m_board[i][2] = 195;
            m_board[i][18] = 180;
        }

        for (size_t i = 2; i < 19; i += 2)
            for (size_t j = 3; j < 19; j += 2)
                m_board[i][j] = 196;

        for (size_t i = 3; i < 18; i += 2)
            for (size_t j = 2; j < 19; j += 2)
                m_board[i][j] = 179;

        for (size_t i = 4; i < 17; i += 2)
            for (size_t j = 4; j < 17; j += 2)
                m_board[i][j] = 197;

        for (size_t i = 4; i < 17; i += 2)
            m_board[2][i] = 194;
        for (size_t i = 4; i < 17; i += 2)
            m_board[18][i] = 193;
        for (size_t i = 4; i < 17; i += 2)
            m_board[i][2] = 195;
        for (size_t i = 4; i < 17; i += 2)
            m_board[i][18] = 180;
    }

    // set nums and letters
    {
        // nums
        for (size_t i = 3, t = 0; i < 19; i += 2, ++t)
            m_board[1][i] = m_board[19][i] = ('1' + t);
        // letters
        for (size_t i = 3, t = 0; i < 19; i += 2, ++t)
            m_board[i][1] = m_board[i][19] = ('A' + t);
    }
}
// put the pieces from the boardString
void Chess::setPieces()
{
    for (size_t row = 0, t = 0; row < 8; ++row)
        for (size_t col = 0; col < 8; ++col, ++t)
            m_board[(3 + (row * 2))][(3 + (col * 2))] = ((m_boardString[t] == '#') ? 32 : m_boardString[t]);
}
// print the only the board to screen
void Chess::show() const
{
    for (size_t row = 0; row < _SIZE; ++row)
    {
        for (size_t col = 0; col < _SIZE; ++col)
            cout << m_board[row][col];
        cout << endl;
    }
}
// clear screen and print the board and the relevant msg
void Chess::displayBoard() const
{
    clear();
    show();
    cout << m_msg<< m_errorMsg;


}
// print the who is turn before getting input
void Chess::showAskInput() const
{
    if (m_turn)
        cout << "Player 1 (White - Capital letters) >> ";
    else
        cout << "Player 2 (Black - Small letters)   >> ";
}
// check if the source and dest are the same
bool Chess::isSame() const
{
    return ((m_input[0] == m_input[2]) && (m_input[1] == m_input[3]));
}
// check if the input is lockations at board
bool Chess::isValid() const
{
    return ((('A' <= m_input[0]) && (m_input[0] <= 'H')) || (('a' <= m_input[0]) && (m_input[0] <= 'h')) &&
                                                            (('1' <= m_input[1]) && (m_input[1] <= '8')) &&
                                                            (('A' <= m_input[2]) && (m_input[2] <= 'H')) || (('a' <= m_input[2]) && (m_input[2] <= 'h')) &&
                                                                                                            (('1' <= m_input[3]) && (m_input[3] <= '8')));
}

// check if the input is exit or quit
bool Chess::isExit() const
{
    return ((m_input == "exit") || (m_input == "quit") || (m_input == "EXIT") || (m_input == "QUIT"));
}
// execute the movement on board
void Chess::excute()
{
    int row = (m_input[0] - 'a');
    int col = (m_input[1] - '1');
    char pieceInSource = m_boardString[(row * 8) + col];
    m_boardString[(row * 8) + col] = '#';

    row = (m_input[2] - 'a');
    col = (m_input[3] - '1');
    m_boardString[(row * 8) + col] = pieceInSource;
    if ((pieceInSource == 'P' && row == 7) || (pieceInSource == 'p' && row == 0)) {
        Location loc;
        loc.row = row;
        loc.column = col;
        promotePawn(loc);
    }
    setPieces();
}
// check the response code and switch turn if needed
void Chess::doTurn() {
    m_errorMsg = "\n";
    try {
        switch (m_codeResponse) {
            case 11:
                throw InvalidMoveException("There is no piece at the source.\n");
            case 12:
                throw InvalidMoveException("The piece in the source belongs to your opponent.\n");
            case 13:
                throw InvalidMoveException("There is one of your pieces at the destination.\n");
            case 21:
                throw InvalidMoveException("Illegal movement of that piece.\n");
            case 31:
                throw CheckmateException("This movement will cause checkmate.\n");
            case 41:
                excute();
                m_turn = !m_turn;
                m_msg = "The last movement was legal and caused check.\n";
                displayBoard(); // Update board display after move
                break;
            case 42:
                excute();
                m_turn = !m_turn;
                m_msg = "The last movement was legal.\n";
                displayBoard(); // Update board display after move
                break;
            case 43:
                executeCastling();
                m_turn = !m_turn;
                m_msg = "The last movement was legal - Castling.\n";
                displayBoard(); // Update board display after move
                break;
            case 44:
                excute();
                m_turn = !m_turn;
                m_msg = "Checkmate! Player " + std::to_string(m_turn ? 1 : 2) + " wins.\n";
                displayBoard(); // Update board display after move
                // Wait for last input before closing
                std::cout << "Press any key to exit...\n";
                std::cin.get();
                exit(0);
                break;
            default:
                throw ChessException("Unknown error occurred.\n");
        }

        // Check for pawn promotion after executing the move
        if (m_input.length() == 4) {
            int startRow = (m_input[1] - '1');
            int destRow = (m_input[3] - '1');
            char piece = m_boardString[(startRow * 8) + (m_input[0] - 'a')];

            if ((piece == 'P' && destRow == 0) || (piece == 'p' && destRow == 7)) {
                Location loc;
                loc.row = destRow;
                loc.column = (m_input[2] - 'a');
                promotePawn(loc);
            }
        }

    } catch (const InvalidMoveException& e) {
        m_msg = e.what();
    } catch (const CheckmateException& e) {
        m_msg = e.what();
    } catch (const ChessException& e) {
        m_msg = e.what();
    }
}



// C'tor
Chess::Chess(const string& start)
        : m_boardString(start),m_codeResponse(-1)
{
    m_inputsToCheckIndex = 0;
    setFrames();
    setPieces();
}

// get the source and destination
string Chess::getInput()
{
    static bool isFirst = true;

    if (!isFirst) {
        doTurn();
    } else {
        isFirst = false;
    }

    displayBoard();

    getPieceMoves();

    showAskInput();

    // Read player input
    std::cin >> m_input;

    // Check for exit command
    if (isExit()) {
        return "exit";
    }

    // Validate input format and ensure it's correct
    while (!isValid() || isSame()) {
        if (!isValid()) {
            m_errorMsg = "Invalid input!!\n";
        } else {
            m_errorMsg = "The source and the destination are the same!!\n";
        }
        displayBoard();
        showAskInput();
        std::cin >> m_input;
        if (isExit()) {
            return "exit";
        }
    }

    // Convert uppercase letters to lowercase
    if (m_input != "exit") {
        if (('A' <= m_input[0]) && (m_input[0] <= 'H')) {
            m_input[0] = (m_input[0] - 'A' + 'a');
        }
        if (('A' <= m_input[2]) && (m_input[2] <= 'H')) {
            m_input[2] = (m_input[2] - 'A' + 'a');
        }
    }

    return m_input;
}

void Chess::setCodeResponse(int codeResponse)
{
    if (((11 <= codeResponse) && (codeResponse <= 13)) ||
        ((21 == codeResponse) || (codeResponse == 31)) ||
        ((41 == codeResponse) || (codeResponse == 42) || (codeResponse == 43) || (codeResponse == 44))) {
        m_codeResponse = codeResponse;
    }
}

void Chess::executeCastling()
{
    int kingRow = m_turn ? 0 : 7; // Assuming white pieces start at row 0, black at row 7

    if (m_input == "a1c1" || m_input == "A1C1" || m_input == "a8c8" || m_input == "A8C8") {
        // Queenside castling
        m_boardString[(kingRow * 8) + 4] = '#'; // Remove King from e1/e8
        m_boardString[(kingRow * 8) + 0] = '#'; // Remove Rook from a1/a8
        m_boardString[(kingRow * 8) + 2] = m_turn ? 'K' : 'k'; // Place King at c1/c8
        m_boardString[(kingRow * 8) + 3] = m_turn ? 'R' : 'r'; // Place Rook at d1/d8
    } else if (m_input == "a1d1" || m_input == "A1D1" || m_input == "a8d8" || m_input == "A8D8") {
        // Kingside castling
        m_boardString[(kingRow * 8) + 4] = '#'; // Remove King from e1/e8
        m_boardString[(kingRow * 8) + 7] = '#'; // Remove Rook from h1/h8
        m_boardString[(kingRow * 8) + 6] = m_turn ? 'K' : 'k'; // Place King at g1/g8
        m_boardString[(kingRow * 8) + 5] = m_turn ? 'R' : 'r'; // Place Rook at f1/f8
    }

    setPieces();
}
void Chess::promotePawn(Location loc) {
    char pawnSymbol = m_boardString[(loc.row * 8) + loc.column]; // Get symbol of the pawn at location

    if (pawnSymbol == 'P') {
        // White pawn promotion
        std::cout << "White pawn promotion! Choose a piece (Q/R/B/N): ";
        char choice;
        std::cin >> choice;

        switch (choice) {
            case 'Q':
            case 'q':
                m_boardString[(loc.row * 8) + loc.column] = 'Q'; // Replace pawn with white queen
                break;
            case 'R':
            case 'r':
                m_boardString[(loc.row * 8) + loc.column] = 'R'; // Replace pawn with white rook
                break;
            case 'B':
            case 'b':
                m_boardString[(loc.row * 8) + loc.column] = 'B'; // Replace pawn with white bishop
                break;
            case 'N':
            case 'n':
                m_boardString[(loc.row * 8) + loc.column] = 'N'; // Replace pawn with white knight
                break;
            default:
                std::cout << "Invalid choice. Defaulting to Queen." << std::endl;
                m_boardString[(loc.row * 8) + loc.column] = 'Q'; // Default to queen if invalid choice
                break;
        }
    } else if (pawnSymbol == 'p') {
        // Black pawn promotion
        std::cout << "Black pawn promotion! Choose a piece (q/r/b/n): ";
        char choice;
        std::cin >> choice;

        switch (choice) {
            case 'q':
                m_boardString[(loc.row * 8) + loc.column] = 'q'; // Replace pawn with black queen
                break;
            case 'r':
                m_boardString[(loc.row * 8) + loc.column] = 'r'; // Replace pawn with black rook
                break;
            case 'b':
                m_boardString[(loc.row * 8) + loc.column] = 'b'; // Replace pawn with black bishop
                break;
            case 'n':
                m_boardString[(loc.row * 8) + loc.column] = 'n'; // Replace pawn with black knight
                break;
            default:
                std::cout << "Invalid choice. Defaulting to queen." << std::endl;
                m_boardString[(loc.row * 8) + loc.column] = 'q'; // Default to queen if invalid choice
                break;
        }
    }
}

std::vector<Location> Chess::getPieceMoves() {
    std::vector<Location> randomMoves;

    // Seed for random number generation
    srand(static_cast<unsigned int>(time(nullptr)));

    // Measure total time taken
    auto total_start = std::chrono::steady_clock::now();

    // Function to generate random moves
    auto generateRandomMoves = [&randomMoves, this]() {
        while (randomMoves.size() < 5) {
            // Generate a random source position
            char rand_col = 'a' + rand() % 8;  // Random column 'a' to 'h'
            char rand_row = '1' + rand() % 8;  // Random row '1' to '8'
            std::string randomSource = { rand_col, rand_row };

            int col = rand_col - 'a';
            int row = rand_row - '1';

            // Get piece from board
            char piece = m_board[(3 + (col * 2))][(3 + (row * 2))];

            // Measure time for move generation
            auto start = std::chrono::steady_clock::now();

            // Function to generate moves for the piece
            auto generatePieceMoves = [this, piece, rand_row, rand_col]() {
                if (m_turn == 1) { // White player's turn
                    switch (piece) {
                        case 'P': {
                            Pawn pawn;
                            return pawn.stepForwardWhitePawn(rand_row, rand_col, m_board);
                        }
                        case 'R': {
                            Rook rook;
                            std::vector<Location> moves;
                            auto horizontalMoves = rook.stepHorizontalRookWhite(rand_row, rand_col, m_board);
                            moves.insert(moves.end(), horizontalMoves.begin(), horizontalMoves.end());
                            auto verticalMoves = rook.stepVerticalRookWhite(rand_row, rand_col, m_board);
                            moves.insert(moves.end(), verticalMoves.begin(), verticalMoves.end());
                            return moves;
                        }
                        case 'N': {
                            Knight knight;
                            return knight.stepKnightWhite(rand_row, rand_col, m_board);
                        }
                        case 'B': {
                            Bishop bishop;
                            return bishop.stepDiagonalBishopWhite(rand_row, rand_col, m_board);
                        }
                        case 'Q': {
                            Queen queen;
                            std::vector<Location> moves;
                            auto horizontalMoves = queen.stepHorizontalQueenWhite(rand_row, rand_col, m_board);
                            moves.insert(moves.end(), horizontalMoves.begin(), horizontalMoves.end());
                            auto verticalMoves = queen.stepVerticalQueenWhite(rand_row, rand_col, m_board);
                            moves.insert(moves.end(), verticalMoves.begin(), verticalMoves.end());
                            auto diagonalMoves = queen.stepDiagonalQueenWhite(rand_row, rand_col, m_board);
                            moves.insert(moves.end(), diagonalMoves.begin(), diagonalMoves.end());
                            return moves;
                        }
                        case 'K': {
                            King king;
                            return king.stepKingWhite(rand_row, rand_col, m_board);
                        }
                        default:
                            return std::vector<Location>{};
                    }
                } else { // Black player's turn
                    switch (piece) {
                        case 'p': {
                            Pawn pawn;
                            return pawn.stepForwardBlackPawn(rand_row, rand_col, m_board);
                        }
                        case 'r': {
                            Rook rook;
                            std::vector<Location> moves;
                            auto horizontalMoves = rook.stepHorizontalRookBlack(rand_row, rand_col, m_board);
                            moves.insert(moves.end(), horizontalMoves.begin(), horizontalMoves.end());
                            auto verticalMoves = rook.stepVerticalRookBlack(rand_row, rand_col, m_board);
                            moves.insert(moves.end(), verticalMoves.begin(), verticalMoves.end());
                            return moves;
                        }
                        case 'n': {
                            Knight knight;
                            return knight.stepKnightBlack(rand_row, rand_col, m_board);
                        }
                        case 'b': {
                            Bishop bishop;
                            return bishop.stepDiagonalBishopBlack(rand_row, rand_col, m_board);
                        }
                        case 'q': {
                            Queen queen;
                            std::vector<Location> moves;
                            auto horizontalMoves = queen.stepHorizontalQueenBlack(rand_row, rand_col, m_board);
                            moves.insert(moves.end(), horizontalMoves.begin(), horizontalMoves.end());
                            auto verticalMoves = queen.stepVerticalQueenBlack(rand_row, rand_col, m_board);
                            moves.insert(moves.end(), verticalMoves.begin(), verticalMoves.end());
                            auto diagonalMoves = queen.stepDiagonalQueenBlack(rand_row, rand_col, m_board);
                            moves.insert(moves.end(), diagonalMoves.begin(), diagonalMoves.end());
                            return moves;
                        }
                        case 'k': {
                            King king;
                            return king.stepKingBlack(rand_row, rand_col, m_board);
                        }
                        default:
                            return std::vector<Location>{};
                    }
                }
            };

            // Asynchronously generate moves for the piece
            auto future_moves = std::async(std::launch::async, generatePieceMoves);

            // Wait for the future to complete and get the results
            std::vector<Location> possibleMoves = future_moves.get();

            // Log generated moves
            for (const auto &loc : possibleMoves) {
                if (randomMoves.size() < 5) {
                    char new_col = loc.column + 'a';
                    char new_row = loc.row + '1';
                    std::cout << "Source: " << randomSource << " -> Destination: " << new_col << new_row << std::endl;
                    moveQueue.push(loc);
                    randomMoves.push_back(loc);
                } else {
                    break;
                }
            }

            auto end = std::chrono::steady_clock::now();
            auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        }
    };

    // Call the function to generate random moves
    generateRandomMoves();

    // Measure total time taken
    auto total_end = std::chrono::steady_clock::now();
    auto total_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(total_end - total_start);
    std::cout << "Total time taken for all moves: " << total_elapsed.count() << " ms" << std::endl;

    return randomMoves;
}

std::chrono::milliseconds Chess::setInputsToCheck(const std::vector<std::string>& inputs, int processNum) {
    m_inputsToCheck = inputs;
    m_inputsToCheckIndex = 0;

    auto start = std::chrono::steady_clock::now();

    switch (processNum) {
        case 1: {
            for (const auto& move : m_inputsToCheck) {
                m_input = move;
                excute();
            }
            break;
        }
        case 2: {
            std::vector<std::thread> threads;
            for (size_t i = 0; i < m_inputsToCheck.size(); ++i) {
                threads.emplace_back([this, i]() {
                    std::lock_guard<std::mutex> lock(inputMutex); // Lock access to shared resources
                    m_input = m_inputsToCheck[i];
                    excute();
                });
            }
            for (auto& thread : threads) {
                thread.join();
            }
            break;
        }
        case 4: {
            std::vector<std::thread> threads;
            size_t chunkSize = m_inputsToCheck.size() / 4;
            for (size_t i = 0; i < 4; ++i) {
                threads.emplace_back([this, i, chunkSize]() {
                    size_t startIdx = i * chunkSize;
                    size_t endIdx = (i == 3) ? m_inputsToCheck.size() : (i + 1) * chunkSize;
                    for (size_t j = startIdx; j < endIdx; ++j) {
                        m_input = m_inputsToCheck[j];
                        excute();
                    }
                });
            }
            for (auto& thread : threads) {
                thread.join();
            }
            break;
        }
        case 8: {
            std::vector<std::thread> threads;
            size_t chunkSize = m_inputsToCheck.size() / 8;
            for (size_t i = 0; i < 8; ++i) {
                threads.emplace_back([this, i, chunkSize]() {
                    size_t startIdx = i * chunkSize;
                    size_t endIdx = (i == 7) ? m_inputsToCheck.size() : (i + 1) * chunkSize;
                    for (size_t j = startIdx; j < endIdx; ++j) {
                        m_input = m_inputsToCheck[j];
                        excute();
                    }
                });
            }
            for (auto& thread : threads) {
                thread.join();
            }
            break;
        }
        default:
            std::cerr << "Invalid number of processes: " << processNum << std::endl;
            break;
    }

    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
}
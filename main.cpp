#include <iostream>
#include <string>
#include <cmath>
#include <list>
#include "chess.h"

float minimax(char chessMap[8][8], int depth, bool isWhiteMove, float alpha, float beta, int* lastMoveCoordinate) {

    std::string currentMove;
    char currentVictim;
    float bestmove = 0;

    if (depth <= 0)
        return evaluatingBoard(chessMap);
    
    std::list <std::string> allPossibleMove = ALL_MOVE_COMBINATION;

    if (!isWhiteMove) {
        bestmove = -1000000.0;
        for (auto it : allPossibleMove) {
            currentMove = it;
            currentVictim = chessMap[8 - currentMove[3] + '0'][currentMove[2] - 97];
            MAKE_MOVE;
            REMEMBER_LAST_MOVE;
            bestmove = fmax(bestmove, minimax(chessMap, depth - 1, !isWhiteMove, alpha, beta, lastMoveCoordinate));
            UNDO_MOVE;

            alpha = fmax(alpha, bestmove);

            if (beta <= alpha)
                return bestmove;
        }
        if (allPossibleMove.size() == 0)
            bestmove = fmax(bestmove, minimax(chessMap, depth - 1, !isWhiteMove, alpha, beta, lastMoveCoordinate));
        return bestmove;
    }
    else {
        bestmove = 1000000.0;
        for (auto it : allPossibleMove) {
            currentMove = it;
            currentVictim = chessMap[8 - currentMove[3] + '0'][currentMove[2] - 97];
            MAKE_MOVE;
            REMEMBER_LAST_MOVE;
            bestmove = fmin(bestmove, minimax(chessMap, depth - 1, !isWhiteMove, alpha, beta, lastMoveCoordinate));
            UNDO_MOVE;

            beta = fmin(beta, bestmove);

            if (beta <= alpha)
                return bestmove;

        }
        if (allPossibleMove.size() == 0)
            bestmove = fmin(bestmove, minimax(chessMap, depth - 1, !isWhiteMove, alpha, beta, lastMoveCoordinate));
        return bestmove;
    }
}
// Getting the number of points in a sequence of moves

std::string minimaxRoot(char chessMap[8][8], bool isWhiteMove, int* lastMoveCoordinate, std::list <std::string> allPossibleMove) {

    std::string currentMove;
    std::string bestMove;
    char currentVictim;
    float score = 0;
    float bestscore = -1000000.0;

    for (auto it : allPossibleMove) {
        currentMove = it;
        currentVictim = chessMap[8 - currentMove[3] + '0'][currentMove[2] - 97];
        MAKE_MOVE;
        score = minimax(chessMap, difficult, true, -1000000.0, 1000000.0, lastMoveCoordinate);
        UNDO_MOVE;

        if (score >= bestscore) {
            bestscore = score;
            bestMove = currentMove;
        }
    }
    return bestMove;
}
// The root of the Minimax, the expense of all possible moves and select the best

inline float evaluatingBoard(char chessMap[8][8]) {
    float totalScore = 0.0;
    for (int y_pos = 1; y_pos <= 8; y_pos++) {
        for (int x_pos = 1; x_pos <= 8; x_pos++) {
            if (chessMap[8 - y_pos][x_pos - 1] != '.')
                totalScore = totalScore + ratingMove(chessMap, x_pos, y_pos);
        }
    }
    return totalScore;
}
// Evaluating the board after a sequence of moves

inline float ratingMove(char chessMap[8][8], int x_pos, int y_pos) {

    if (chessMap[8 - y_pos][x_pos - 1] == 'p')
        return 10.0 + blackPawnScore[8 - y_pos][x_pos - 1];
    else if (chessMap[8 - y_pos][x_pos - 1] == 'P')
        return -10.0 + whitePawnScore[8 - y_pos][x_pos - 1];
    else if (chessMap[8 - y_pos][x_pos - 1] == 'b')
        return 35.0 + blackBishopScore[8 - y_pos][x_pos - 1];
    else if (chessMap[8 - y_pos][x_pos - 1] == 'B')
        return -35.0 + whiteBishopScore[8 - y_pos][x_pos - 1];
    else if (chessMap[8 - y_pos][x_pos - 1] == 'n')
        return 30.0 + blackKnightScore[8 - y_pos][x_pos - 1];
    else if (chessMap[8 - y_pos][x_pos - 1] == 'N')
        return -30.0 + whiteKnightScore[8 - y_pos][x_pos - 1];
    else if (chessMap[8 - y_pos][x_pos - 1] == 'r')
        return 50.0 + blackRookScore[8 - y_pos][x_pos - 1];
    else if (chessMap[8 - y_pos][x_pos - 1] == 'R')
        return -50.0 + whiteRookScore[8 - y_pos][x_pos - 1];
    else if (chessMap[8 - y_pos][x_pos - 1] == 'q')
        return 70.0 + QueenScore[8 - y_pos][x_pos - 1];
    else if (chessMap[8 - y_pos][x_pos - 1] == 'Q')
        return -70.0 + QueenScore[8 - y_pos][x_pos - 1];
    else if (chessMap[8 - y_pos][x_pos - 1] == 'k')
        return 100.0 + blackKingScore[8 - y_pos][x_pos - 1];
    else if (chessMap[8 - y_pos][x_pos - 1] == 'K')
        return -100.0 + whiteKingScore[8 - y_pos][x_pos - 1];
}
// Assessment of the data's coordinate on the field

std::list <std::string> changeCheckAndCastlingMove(char chessMap[8][8], bool isWhiteMove, int* lastMoveCoordinate, std::list <std::string> allPossibleMove, std::list <std::string> allPossibleEnemyMove) {
    std::list <std::string> changedPossibleMove;
    std::string currentMove;
    char currentVictim;
    bool isPointCheck[10] = {};

    for (auto it : allPossibleEnemyMove) {
        currentMove = it;
        if (currentMove[2] == 'b' && currentMove[3] == '8')
            isPointCheck[0] = true;
        if (currentMove[2] == 'c' && currentMove[3] == '8')
            isPointCheck[1] = true;
        if (currentMove[2] == 'd' && currentMove[3] == '8')
            isPointCheck[2] = true;

        if (currentMove[2] == 'g' && currentMove[3] == '8')
            isPointCheck[3] = true;
        if (currentMove[2] == 'f' && currentMove[3] == '8')
            isPointCheck[4] = true;

        if (currentMove[2] == 'b' && currentMove[3] == '1')
            isPointCheck[5] = true;
        if (currentMove[2] == 'c' && currentMove[3] == '1')
            isPointCheck[6] = true;
        if (currentMove[2] == 'd' && currentMove[3] == '1')
            isPointCheck[7] = true;

        if (currentMove[2] == 'g' && currentMove[3] == '1')
            isPointCheck[8] = true;
        if (currentMove[2] == 'f' && currentMove[3] == '1')
            isPointCheck[9] = true;
    }

    if (BLACK_MOVE) {
        if (!blackKingMoved && !blackLeftRookMoved && chessMap[0][1] == '.' && chessMap[0][2] == '.' && chessMap[0][3] == '.' && !isPointCheck[0] && !isPointCheck[1] && !isPointCheck[2] && chessMap[0][4] == 'k' && chessMap[0][0] == 'r')
            changedPossibleMove.push_back("e8c8");
        if (!blackKingMoved && !blackRightRookMoved && chessMap[0][6] == '.' && chessMap[0][5] == '.' && !isPointCheck[3] && !isPointCheck[4] && chessMap[0][4] == 'k' && chessMap[0][7] == 'r')
            changedPossibleMove.push_back("e8g8");
    }
    else {
        if (!whiteKingMoved && !whiteLeftRookMoved && chessMap[7][1] == '.' && chessMap[7][2] == '.' && chessMap[7][3] == '.' && !isPointCheck[5] && !isPointCheck[6] && !isPointCheck[7] && chessMap[7][4] == 'K' && chessMap[7][0] == 'R')
            changedPossibleMove.push_back("e1c1");
        if (!whiteKingMoved && !whiteRightRookMoved && chessMap[7][6] == '.' && chessMap[7][5] == '.' && !isPointCheck[8] && !isPointCheck[9] && chessMap[7][4] == 'K' && chessMap[7][7] == 'R')
            changedPossibleMove.push_back("e1g1");
    }

    for (auto it : changedPossibleMove)
        allPossibleMove.push_back(it);

    for (auto it : allPossibleMove) {
        currentMove = it;
        currentVictim = chessMap[8 - currentMove[3] + '0'][currentMove[2] - 97];
        MAKE_MOVE;
        if (!checkingCheck(chessMap, gettingAllFigureMove(chessMap, !isWhiteMove, lastMoveCoordinate)))
            changedPossibleMove.push_back(currentMove);

        UNDO_MOVE;

    }

    return changedPossibleMove;
}
// Fix all possible moves, add castling to them, and ban the move under the check

std::list <std::string> gettingAllFigureMove(char chessMap[8][8], bool isWhiteMove, int* lastMoveCoordinate) {
    int moveCoordinate[4];
    std::string coordinateMove = "    ";

    std::list <std::string> allPossibleMove;

    for (int x_from = 1; x_from <= 8; x_from++) {
        for (int y_from = 1; y_from <= 8; y_from++) {
            if (chessMap[8 - x_from][y_from - 1] != '.') {
                moveCoordinate[1] = x_from;
                moveCoordinate[0] = y_from;
                for (int y_to = 1; y_to <= 8; y_to++) {
                    for (int x_to = 1; x_to <= 8; x_to++) {
                        moveCoordinate[3] = y_to;
                        moveCoordinate[2] = x_to;
                        if (checkingInput(moveCoordinate, chessMap, isWhiteMove, lastMoveCoordinate)) {
                            coordinateMove[0] = char(y_from + 96);
                            coordinateMove[1] = char(x_from + '0');
                            coordinateMove[2] = char(x_to + 96);
                            coordinateMove[3] = char(y_to + '0');
                            allPossibleMove.push_back(coordinateMove);
                        }
                    }
                }
            }
        }
    }
    return allPossibleMove;
}
// Getting all possible moves of a single player, except castling and " check moves"

inline bool checkingMate(char chessMap[8][8], bool isWhiteMove, int* lastMoveCoordinate, std::list <std::string> allPossibleMove) {

    if (allPossibleMove.size() == 0 && checkingCheck(chessMap, changeCheckAndCastlingMove(chessMap, isWhiteMove, lastMoveCoordinate, gettingAllFigureMove(chessMap, !isWhiteMove, lastMoveCoordinate), gettingAllFigureMove(chessMap, !isWhiteMove, lastMoveCoordinate)))) {
        checkMate = true;
        return true;
    }
    return false;
}
// Checking for Checkmate

inline bool checkingStalemate(char chessMap[8][8], std::list <std::string> allPossibleMove) {
    if (allPossibleMove.size() == 0) {
        stalemate = true;
        return true;
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (chessMap[i][j] != 'K' && chessMap[i][j] != 'k' && chessMap[i][j] != '.')
                return false;
        }
    }
    stalemate = true;
    return true;
}
// Checking for Stalemate

inline bool checkingCheck(char chessMap[8][8], std::list <std::string> allPossibleMove) {
    std::string currentMove;

    for (auto it : allPossibleMove) {
        currentMove = it;

        if (chessMap[8 - currentMove[3] + '0'][currentMove[2] - 97] == 'k')
            return true;

        if (chessMap[8 - currentMove[3] + '0'][currentMove[2] - 97] == 'K')
            return true;

    }
    return false;
}
// Checkinh for Check

inline bool movingStraight(int* moveCoordinate, char chessMap[8][8]) {

    int diff_x = 0;
    int diff_y = 0;
    int x = MOVING_FROM_X;
    int y = MOVING_FROM_Y;

    if (MOVING_TO_X - MOVING_FROM_X < 0)
        diff_x = -1;
    if (MOVING_TO_X - MOVING_FROM_X > 0)
        diff_x = 1;
    if (MOVING_TO_Y - MOVING_FROM_Y < 0)
        diff_y = -1;
    if (MOVING_TO_Y - MOVING_FROM_Y > 0)
        diff_y = 1;

    do {
        x += diff_x;
        y += diff_y;

        if (x == MOVING_TO_X && y == MOVING_TO_Y)
            return true;
    } while (chessMap[8 - y][x - 1] == '.');

    return false;
}
// Checking if there is another shape in the path of the shape

inline bool checkingInput(int* moveCoordinate, char chessMap[8][8], bool isWhiteMove, int* lastMoveCoordinate) {

    if (MOVING_FROM_X > 8 || MOVING_FROM_X < 0)
        return false;
    else if (MOVING_FROM_Y > 8 || MOVING_FROM_Y < 0)
        return false;
    else if (MOVING_TO_X > 8 || MOVING_TO_X < 0)
        return false;
    else if (MOVING_TO_Y > 8 || MOVING_TO_Y < 0)
        return false;

    else if (MOVING_FROM_X == MOVING_TO_X && MOVING_FROM_Y == MOVING_TO_Y)
        return false;
    else if (BLACK_MOVE && FIGURE_POINT > 'A' && FIGURE_POINT < 'Z')
        return false;
    else if (WHITE_MOVE && FIGURE_POINT > 'a' && FIGURE_POINT < 'z')
        return false;
    else if (FIGURE_POINT < 'Z' && FIGURE_POINT > 'A' && MOVE_POINT < 'Z' && MOVE_POINT > 'A')
        return false;
    else if (FIGURE_POINT < 'z' && FIGURE_POINT > 'a' && MOVE_POINT < 'z' && MOVE_POINT > 'a')
        return false;
    else if (FIGURE_POINT == '.')
        return false;

    else if (FIGURE_POINT == 'K') {
        if (ABS_DELTA_X <= 1 && ABS_DELTA_Y <= 1)
            return true;

        return false;
    }
    else if (FIGURE_POINT == 'k') {
        if (ABS_DELTA_X <= 1 && ABS_DELTA_Y <= 1)
            return true;

        return false;
    }

    else if (FIGURE_POINT == 'n' || FIGURE_POINT == 'N') {
        if (ABS_DELTA_X == 1 && ABS_DELTA_Y == 2)
            return true;
        else if (ABS_DELTA_X == 2 && ABS_DELTA_Y == 1)
            return true;
        return false;
    }

    else if (FIGURE_POINT == 'r') {
        if ((DELTA_X == 0 || DELTA_Y == 0)) {
            if (movingStraight(moveCoordinate, chessMap))
                return true;
        }
        return false;
    }
    else if (FIGURE_POINT == 'R') {
        if ((DELTA_X == 0 || DELTA_Y == 0)) {
            if (movingStraight(moveCoordinate, chessMap))
                return true;
        }
        return false;
    }

    else if (FIGURE_POINT == 'b' || FIGURE_POINT == 'B') {
        if ((DELTA_Y != 0 && DELTA_X != 0))
            return movingStraight(moveCoordinate, chessMap);
        return false;
    }
    else if (FIGURE_POINT == 'p' || FIGURE_POINT == 'P') {
        if (chessMap[8 - lastMoveCoordinate[3]][lastMoveCoordinate[2] - 1] == 'p' && lastMoveCoordinate[3] - lastMoveCoordinate[1] == -2 && abs(moveCoordinate[0] - lastMoveCoordinate[2]) == 1 && moveCoordinate[1] == lastMoveCoordinate[3] && moveCoordinate[2] == lastMoveCoordinate[2] && moveCoordinate[3] == lastMoveCoordinate[1] - 1)
            return true;
        else if (chessMap[8 - lastMoveCoordinate[3]][lastMoveCoordinate[2] - 1] == 'P' && lastMoveCoordinate[3] - lastMoveCoordinate[1] == 2 && abs(moveCoordinate[0] - lastMoveCoordinate[2]) == 1 && moveCoordinate[1] == lastMoveCoordinate[3] && moveCoordinate[2] == lastMoveCoordinate[2] && moveCoordinate[3] == lastMoveCoordinate[1] + 1)
            return true;
        else if (MOVE_POINT == '.' && DELTA_X == 0 && (WHITE_MOVE && DELTA_Y == -1 || BLACK_MOVE && DELTA_Y == 1))
            return true;
        else if (MOVE_POINT == '.' && DELTA_X == 0 && (MOVING_FROM_Y == 2 || MOVING_FROM_Y == 7) && ((WHITE_MOVE && DELTA_Y == -2 && chessMap[8 - MOVING_FROM_Y - 1][MOVING_FROM_X - 1] == '.') || (BLACK_MOVE && DELTA_Y == 2 && chessMap[8 - MOVING_FROM_Y + 1][MOVING_FROM_X - 1] == '.')))
            return true;
        else if (MOVE_POINT != '.' && ABS_DELTA_X == 1 && (WHITE_MOVE && DELTA_Y == -1 || BLACK_MOVE && DELTA_Y == 1))
            return true;
        return false;
    }
    else if (FIGURE_POINT == 'q' || FIGURE_POINT == 'Q')
        return movingStraight(moveCoordinate, chessMap);
}
// Checking moves for validity

inline void movingFigure(char chessMap[8][8], int* moveCoordinate, int* lastMoveCoordinate, std::list <std::string> allPossibleMove) {
    std::string currentMove;
    int chooseFigure;

    if (FIGURE_POINT == 'r' && MOVING_FROM_X == 1)
        blackLeftRookMoved = true;
    else if (FIGURE_POINT == 'r' && MOVING_FROM_X == 8)
        blackRightRookMoved = true;
    else if (FIGURE_POINT == 'R' && MOVING_FROM_X == 1)
        whiteLeftRookMoved = true;
    else if (FIGURE_POINT == 'R' && MOVING_FROM_X == 8)
        whiteRightRookMoved = true;
    else if (FIGURE_POINT == 'k')
        blackKingMoved = true;
    else if (FIGURE_POINT == 'K')
        whiteKingMoved = true;

    if ((chessMap[8 - moveCoordinate[1]][moveCoordinate[0] - 1] == 'p' || chessMap[8 - moveCoordinate[1]][moveCoordinate[0] - 1] == 'P') && chessMap[8 - moveCoordinate[3]][moveCoordinate[2] - 1] == '.' && ABS_DELTA_X)
        chessMap[8 - lastMoveCoordinate[3]][lastMoveCoordinate[2] - 1] = '.';

    for (auto it : allPossibleMove) {
        if (MOVING_FROM_Y == 1 && MOVING_FROM_X == 5 && MOVING_TO_X == 7 && MOVING_TO_Y == 1 && it == "e1g1") {
            chessMap[7][5] = 'R';
            chessMap[7][7] = '.';
            whiteKingMoved = true;
        }
        else if (MOVING_FROM_Y == 1 && MOVING_FROM_X == 5 && MOVING_TO_X == 3 && MOVING_TO_Y == 1 && it == "e1c1") {
            chessMap[7][3] = 'R';
            chessMap[7][0] = '.';
            whiteKingMoved = true;
        }

        else if (MOVING_FROM_Y == 8 && MOVING_FROM_X == 5 && MOVING_TO_X == 7 && MOVING_TO_Y == 8 && it == "e8g8") {
            chessMap[0][5] = 'r';
            chessMap[0][7] = '.';
            blackKingMoved = true;
        }
        else if (MOVING_FROM_Y == 8 && MOVING_FROM_X == 5 && MOVING_TO_X == 3 && MOVING_TO_Y == 8 && it == "e8c8") {
            chessMap[0][3] = 'r';
            chessMap[0][0] = '.';
            blackKingMoved = true;
        }
    }

    MOVE_POINT = FIGURE_POINT;
    FIGURE_POINT = '.';

    if (MOVE_POINT == 'P' && MOVING_TO_Y == 8) {
        std::cout << "\n" << "Choose figure to promotion of a pawn Q - 1, N - 2, B - 3, R - 4: ";
        std::cin >> chooseFigure;
        if (chooseFigure == 1)
            MOVE_POINT = 'Q';
        if (chooseFigure == 2)
            MOVE_POINT = 'N';
        if (chooseFigure == 3)
            MOVE_POINT = 'B';
        if (chooseFigure == 4)
            MOVE_POINT = 'R';
    }

    if (MOVE_POINT == 'p' && MOVING_TO_Y == 1)
        MOVE_POINT = 'q';

    drawingMap(chessMap);

}
// The movement of the piece, as well as the execution of the passant, castling, and pawn transformation

inline void drawingMap(const char chessMap[8][8]) {
    system("cls");
    std::cout << std::endl;
    for (int i = 0; i < 8; i++) {
        std::cout << 8 - i << "  ";
        for (int j = 0; j < 8; j++) {
            std::cout << chessMap[i][j] << " ";
        }
        std::cout << "\n";
    }

    std::cout << " " << std::endl << "   a b c d e f g h " << std::endl;

}
// Displaying the game board on the screen

void gettingInput(char chessMap[8][8], bool isWhiteMove, int* lastMoveCoordinate, std::string &lastMove) {

    std::string commitMove;
    int moveCoordinate[4];
    int countAllMove = 1;
    std::list <std::string> allPossibleMove = changeCheckAndCastlingMove(chessMap, isWhiteMove, lastMoveCoordinate, gettingAllFigureMove(chessMap, isWhiteMove, lastMoveCoordinate), gettingAllFigureMove(chessMap, !isWhiteMove, lastMoveCoordinate));

    if (checkingMate(chessMap, isWhiteMove, lastMoveCoordinate, ALL_MOVE_COMBINATION))
        return void();

    if (checkingStalemate(chessMap, ALL_MOVE_COMBINATION))
        return void();


error:
    if (BLACK_MOVE)
        commitMove = minimaxRoot(chessMap, isWhiteMove, lastMoveCoordinate, allPossibleMove);
    else {
        std::cin >> commitMove;
        for (auto it : allPossibleMove) {
            if (it == commitMove)
                break;
            if (countAllMove == allPossibleMove.size()) {
                countAllMove = 1;
                goto error;
            }
            countAllMove++;
        }
    }

    MOVING_FROM_X = commitMove[0] - 96;
    MOVING_FROM_Y = commitMove[1] - '0';
    MOVING_TO_X = commitMove[2] - 96;
    MOVING_TO_Y = commitMove[3] - '0';

    movingFigure(chessMap, moveCoordinate, lastMoveCoordinate, allPossibleMove);

    lastMoveCoordinate[0] = MOVING_FROM_X;
    lastMoveCoordinate[1] = MOVING_FROM_Y;
    lastMoveCoordinate[2] = MOVING_TO_X;
    lastMoveCoordinate[3] = MOVING_TO_Y;

    lastMove = commitMove;

}
// Getting a move and checking it

int main() {

    int lastMoveCoordinate[4] = {};
    char chessMap[8][8] = { 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r',
                            'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
                            '.', '.', '.', '.', '.', '.', '.', '.',
                            '.', '.', '.', '.', '.', '.', '.', '.',
                            '.', '.', '.', '.', '.', '.', '.', '.',
                            '.', '.', '.', '.', '.', '.', '.', '.',
                            'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
                            'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R' };
    bool isWhiteMove = true;
    std::string lastMove;

    std::cout << "Choose difficult 1-3" << std::endl;

    std::cin >> difficult;

    drawingMap(chessMap);

    while (!checkMate && !stalemate) {
        if (isWhiteMove) {
            if (checkingCheck(chessMap, gettingAllFigureMove(chessMap, !isWhiteMove, lastMoveCoordinate)))
                std::cout << std::endl << "CHECK";
            std::cout << std::endl << "Last AI's Move: " << lastMove << std::endl;
            std::cout << "Your Turn: ";
        }
        else
            std::cout << std::endl << "AI's Turn ";
        gettingInput(chessMap, isWhiteMove, lastMoveCoordinate, lastMove);
        isWhiteMove = !isWhiteMove;
    }

    if (stalemate)
        std::cout << "STALEMATE";
    else if (checkMate)
        std::cout << "CHECKMATE";
}

// main

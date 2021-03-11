#ifndef _CHESS_H
#define _CHESS_H

#define MOVING_FROM_X moveCoordinate[0]
#define MOVING_FROM_Y moveCoordinate[1]
#define MOVING_TO_X moveCoordinate[2]
#define MOVING_TO_Y moveCoordinate[3]

#define FIGURE_POINT chessMap[8 - MOVING_FROM_Y][MOVING_FROM_X - 1]
#define MOVE_POINT chessMap[8 - MOVING_TO_Y][MOVING_TO_X - 1]

#define ABS_DELTA_X abs(MOVING_FROM_X - MOVING_TO_X)
#define ABS_DELTA_Y abs(MOVING_FROM_Y - MOVING_TO_Y)
#define DELTA_Y MOVING_FROM_Y - MOVING_TO_Y
#define DELTA_X MOVING_FROM_X - MOVING_TO_X

#define BLACK_MOVE isWhiteMove == 0
#define WHITE_MOVE isWhiteMove == 1

#define MAKE_MOVE chessMap[8 - currentMove[3] + '0'][currentMove[2] - 97] = chessMap[8 - currentMove[1] + '0'][currentMove[0] - 97]; chessMap[8 - currentMove[1] + '0'][currentMove[0] - 97] = '.'
#define UNDO_MOVE chessMap[8 - currentMove[1] + '0'][currentMove[0] - 97] = chessMap[8 - currentMove[3] + '0'][currentMove[2] - 97]; chessMap[8 - currentMove[3] + '0'][currentMove[2] - 97] = currentVictim
#define REMEMBER_LAST_MOVE lastMoveCoordinate[0] = currentMove[0] - 96; lastMoveCoordinate[1] = currentMove[1] - '0'; lastMoveCoordinate[2] = currentMove[2] - 96; lastMoveCoordinate[3] = currentMove[3] - '0'

#define ALL_MOVE_COMBINATION changeCheckAndCastlingMove(chessMap, isWhiteMove, lastMoveCoordinate, gettingAllFigureMove(chessMap, isWhiteMove, lastMoveCoordinate), gettingAllFigureMove(chessMap, !isWhiteMove, lastMoveCoordinate))


std::list <std::string> changeCheckAndCastlingMove(char chessMap[8][8], bool isWhiteMove, int* lastMoveCoordinate, std::list <std::string> allPossibleMove, std::list <std::string> allPossibleEnemyMove);
std::list <std::string> gettingAllFigureMove(char chessMap[8][8], bool isWhiteMove, int* lastMoveCoordinate);
inline bool checkingMate(char chessMap[8][8], bool isWhiteMove, int* lastMoveCoordinate, std::list <std::string> allPossibleMove);
inline bool checkingInput(int* moveCoordinate, char chessMap[8][8], bool isWhiteMove, int* lastMoveCoordinate);
inline bool checkingStalemate(char chessMap[8][8], std::list <std::string> allPossibleMove);
inline bool checkingCheck(char chessMap[8][8], std::list <std::string> allPossibleMove);
inline bool movingStraight(int* moveCoordinate, char chessMap[8][8]);
inline void movingFigure(char chessMap[8][8], int* moveCoordinate, int* lastMoveCoordinate, std::list <std::string> allPossibleMove);
void gettingInput(char chessMap[8][8], bool isWhiteMove, int* lastMoveCoordinate, std::string &lastMove);
inline void drawingMap(const char chessMap[8][8]);
inline float ratingMove(char chessMap[8][8], int x_pos, int y_pos);
inline float evaluatingBoard(char chessMap[8][8]);


int difficult = -1;
bool blackLeftRookMoved = false;
bool blackRightRookMoved = false;
bool whiteLeftRookMoved = false;
bool whiteRightRookMoved = false;
bool blackKingMoved = false;
bool whiteKingMoved = false;
bool checkMate = false;
bool stalemate = false;


float blackKingScore[8][8] = { 0.5,  0.0 , 0.7,  0.0,  0.0,  0.0,  0.7,  0.5,
                                 0.5,  0.5,  0.0,  0.0,  0.0,  0.0,  0.5,  0.5,
                                -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0,
                                -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0,
                                -1.0, -1.0, -2.0, -2.0, -2.0, -2.0, -1.0, -1.0,
                                -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0,
                                -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0,
                                -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0 };

float whiteKingScore[8][8] = { -1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0,
                                -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0,
                                -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0,
                                -1.0, -1.0, -2.0, -2.0, -2.0, -1.0, -1.0, -1.0,
                                -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0,
                                -1.0, -1.0, -1.0, -1.0, -2.0, -1.0, -1.0, -1.0,
                                 0.5,  0.5,  0.0,  0.0,  0.0,  0.0,  0.5,  0.5,
                                 0.5,  0.0,  0.7,  0.0,  0.0,  0.0,  0.7,  0.5 };

float blackBishopScore[8][8] = { -2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0,
                                -1.0,  0.5,  0.0,  0.0,  0.0,  0.0,  0.5, -1.0,
                                -1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0, -1.0,
                                -1.0,  0.0,  1.0,  1.0,  1.0,  1.0,  0.0, -1.0,
                                -1.0,  0.5,  0.5,  1.0,  1.0,  0.5,  0.5, -1.0,
                                -1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0,
                                -1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0,
                                -2.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -2.0 };

float whiteBishopScore[8][8] = { -2.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -2.0,
                                -1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0,
                                -1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0,
                                -1.0,  0.5,  0.5,  1.0,  1.0,  0.5,  0.5, -1.0,
                                -1.0,  0.0,  1.0,  1.0,  1.0,  1.0,  0.0, -1.0,
                                -1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0, -1.0,
                                -1.0,  0.5,  0.0,  0.0,  0.0,  0.0,  0.5, -1.0,
                                -2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0 };


float blackKnightScore[8][8] = { -5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0,
                                -4.0, -2.0,  0.0,  0.5,  0.5,  0.0, -2.0, -4.0,
                                -3.0,  0.0,  1.5,  1.0,  1.0,  1.5,  0.0, -3.0,
                                -3.0,  0.5,  1.0,  1.5,  1.5,  1.0,  0.5, -3.0,
                                -3.0,  0.0,  1.0,  1.5,  1.5,  1.0,  0.0, -3.0,
                                -3.0,  0.5,  0.5,  1.0,  1.0,  0.5,  0.5, -3.0,
                                -4.0, -2.0,  0.0,  0.5,  0.5,  0.0, -2.0, -4.0,
                                -5.0, -4.0, -3.0, -3.0, -3.0, -3.0,  4.0, -5.0 };

float whiteKnightScore[8][8] = { -5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0,
                                -4.0, -2.0,  0.0,  0.0,  0.0,  0.0, -2.0, -4.0,
                                -3.0,  0.0,  0.5,  1.0,  1.0,  0.5,  0.5, -3.0,
                                -3.0,  0.0,  1.0,  1.5,  1.5,  1.0,  0.0, -3.0,
                                -3.0,  0.0,  1.0,  1.5,  1.5,  1.0,  0.0, -3.0,
                                -3.0,  0.5,  1.5,  1.0,  1.0,  1.5,  0.5, -3.0,
                                -4.0, -2.0,  0.0,  0.5,  0.5,  0.0, -2.0, -4.0,
                                -5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0 };


float QueenScore[8][8] = { -2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0,
                           -1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0,
                           -1.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0,
                           -0.5,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5,
                            0.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5,
                           -1.0,  0.5,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0,
                           -1.0,  0.0,  0.5,  0.0,  0.0,  0.0,  0.0, -1.0,
                           -2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0 };


float blackRookScore[8][8] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                               -0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,-0.5,
                               -0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,-0.5,
                               -0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,-0.5,
                               -0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,-0.5,
                               -0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,-0.5,
                                0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5,
                                0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

float whiteRookScore[8][8] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5,
                               -0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,-0.5,
                               -0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,-0.5,
                               -0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,-0.5,
                               -0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,-0.5,
                               -0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,-0.5,
                                0.0, 0.0, 0.0, 0.5, 0.5, 0.0, 0.0, 0.0 };

float blackPawnScore[8][8] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                               0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                               0.5,-0.5,-1.0, 1.0, 0.0,-1.0,-0.5, 0.5,
                               0.0, 0.0, 0.0, 2.0, 3.0, 0.0, 0.0, 0.0,
                               0.5, 0.5, 1.0, 1.5, 1.5, 1.0, 0.5, 0.5,
                               0.5, 0.5, 1.0, 2.0, 2.0, 1.0, 0.5, 0.5,
                               5.0, 5.0, 6.0, 6.0, 6.0, 6.0, 5.0, 5.0,
                               9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0 };

float whitePawnScore[8][8] = { 9.0, 9.0, 9.0, 9.0, 9.0, 9.0, 9.0,  9.0,
                              5.0, 5.0, 6.0, 6.0, 6.0, 6.0, 5.0,  5.0,
                              0.5, 0.5, 1.0, 2.0, 2.0, 1.0, 0.5,  0.5,
                              0.5, 0.5, 1.0, 1.5, 1.5, 1.0, 0.5,  0.5,
                              0.0, 0.0, 0.0, 2.0, 3.0, 0.0, 0.0,  0.0,
                              0.5,-0.5,-1.0, 1.0, 0.0,-1.0,-0.5,  0.5,
                              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,  0.0,
                              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,  0.0 };

#endif;

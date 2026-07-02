#ifndef CHESS_GAME_H
#define CHESS_GAME_H
#include <iostream>
#include <string>
const int WHITE = 1;
const int BLACK = 2;
const int EMPTY = 0;
// Base Class
class Piece {
protected:
    int color;
    char symbol;
public:
    Piece(int c, char s);
    int getColor();
    char getSymbol();
    virtual bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]) = 0;
    virtual ~Piece();
};

// Piece Subclasses
class Pawn : public Piece {
public:
    Pawn(int c);
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]) override;
};

class Rook : public Piece {
public:
    Rook(int c);
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]) override;
};

class Knight : public Piece {
public:
    Knight(int c);
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]) override;
};

class Bishop : public Piece {
public:
    Bishop(int c);
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]) override;
};

class Queen : public Piece {
public:
    Queen(int c);
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]) override;
};

class King : public Piece {
public:
    King(int c);
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]) override;
};

// Board Class
class Board {
private:
    Piece* grid[8][8];
public:
    Board();
    ~Board();
    void setupPieces();
    void display();
    Piece* getPiece(int r, int c);
    bool movePiece(int fromRow, int fromCol, int toRow, int toCol);
    bool kingAlive(int color);
};

// Game Class
class Game {
private:
    Board board;
    int currentTurn;
    int colToIndex(char c);
    int rowToIndex(int r);
public:
    Game();
    void printWelcome();
    void run();
};
#endif
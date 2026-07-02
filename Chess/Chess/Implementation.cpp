#include "Header.h"
#include <cmath>

using namespace std;

// --- Piece Implementation ---
Piece::Piece(int c, char s) : color(c), symbol(s) {}
int Piece::getColor() { return color; }
char Piece::getSymbol() { return symbol; }
Piece::~Piece() {}

// --- Pawn ---
Pawn::Pawn(int c) : Piece(c, (c == WHITE) ? 'P' : 'p') {}
bool Pawn::isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]) {
    int direction = (color == WHITE) ? -1 : 1;
    int startRow = (color == WHITE) ? 6 : 1;
    if (fromCol == toCol && toRow == fromRow + direction && board[toRow][toCol] == nullptr) return true;
    if (fromCol == toCol && fromRow == startRow && toRow == fromRow + 2 * direction &&
        board[fromRow + direction][fromCol] == nullptr && board[toRow][toCol] == nullptr) return true;
    if (abs(toCol - fromCol) == 1 && toRow == fromRow + direction &&
        board[toRow][toCol] != nullptr && board[toRow][toCol]->getColor() != color) return true;
    return false;
}

// --- Rook ---
Rook::Rook(int c) : Piece(c, (c == WHITE) ? 'R' : 'r') {}
bool Rook::isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]) {
    if (fromRow != toRow && fromCol != toCol) return false;
    if (fromRow == toRow) {
        int step = (toCol > fromCol) ? 1 : -1;
        for (int c = fromCol + step; c != toCol; c += step) if (board[fromRow][c] != nullptr) return false;
    }
    else {
        int step = (toRow > fromRow) ? 1 : -1;
        for (int r = fromRow + step; r != toRow; r += step) if (board[r][fromCol] != nullptr) return false;
    }
    return (board[toRow][toCol] == nullptr || board[toRow][toCol]->getColor() != color);
}

// --- Knight ---
Knight::Knight(int c) : Piece(c, (c == WHITE) ? 'N' : 'n') {}
bool Knight::isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]) {
    int dr = abs(toRow - fromRow);
    int dc = abs(toCol - fromCol);
    if (!((dr == 2 && dc == 1) || (dr == 1 && dc == 2))) return false;
    return (board[toRow][toCol] == nullptr || board[toRow][toCol]->getColor() != color);
}

// --- Bishop ---
Bishop::Bishop(int c) : Piece(c, (c == WHITE) ? 'B' : 'b') {}
bool Bishop::isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]) {
    int dr = abs(toRow - fromRow), dc = abs(toCol - fromCol);
    if (dr != dc || dr == 0) return false;
    int stepR = (toRow > fromRow) ? 1 : -1, stepC = (toCol > fromCol) ? 1 : -1;
    int r = fromRow + stepR, c = fromCol + stepC;
    while (r != toRow && c != toCol) {
        if (board[r][c] != nullptr) return false;
        r += stepR; c += stepC;
    }
    return (board[toRow][toCol] == nullptr || board[toRow][toCol]->getColor() != color);
}

// --- Queen ---
Queen::Queen(int c) : Piece(c, (c == WHITE) ? 'Q' : 'q') {}
bool Queen::isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]) {
    int dr = abs(toRow - fromRow), dc = abs(toCol - fromCol);
    if (!(fromRow == toRow || fromCol == toCol) && (dr != dc || dr == 0)) return false;
    int stepR = (toRow > fromRow) ? 1 : (toRow < fromRow ? -1 : 0);
    int stepC = (toCol > fromCol) ? 1 : (toCol < fromCol ? -1 : 0);
    int r = fromRow + stepR, c = fromCol + stepC;
    while (r != toRow || c != toCol) {
        if (board[r][c] != nullptr) return false;
        r += stepR; c += stepC;
    }
    return (board[toRow][toCol] == nullptr || board[toRow][toCol]->getColor() != color);
}

// --- King ---
King::King(int c) : Piece(c, (c == WHITE) ? 'K' : 'k') {}
bool King::isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]) {
    return (abs(toRow - fromRow) <= 1 && abs(toCol - fromCol) <= 1) &&
        (board[toRow][toCol] == nullptr || board[toRow][toCol]->getColor() != color);
}

// --- Board Implementation ---
Board::Board() {
    for (int r = 0; r < 8; r++) for (int c = 0; c < 8; c++) grid[r][c] = nullptr;
    setupPieces();
}

void Board::setupPieces() {
    grid[0][0] = new Rook(BLACK); grid[0][1] = new Knight(BLACK); grid[0][2] = new Bishop(BLACK);
    grid[0][3] = new Queen(BLACK); grid[0][4] = new King(BLACK); grid[0][5] = new Bishop(BLACK);
    grid[0][6] = new Knight(BLACK); grid[0][7] = new Rook(BLACK);
    for (int c = 0; c < 8; c++) grid[1][c] = new Pawn(BLACK);
    grid[7][0] = new Rook(WHITE); grid[7][1] = new Knight(WHITE); grid[7][2] = new Bishop(WHITE);
    grid[7][3] = new Queen(WHITE); grid[7][4] = new King(WHITE); grid[7][5] = new Bishop(WHITE);
    grid[7][6] = new Knight(WHITE); grid[7][7] = new Rook(WHITE);
    for (int c = 0; c < 8; c++) grid[6][c] = new Pawn(WHITE);
}

void Board::display() {
    cout << "\n    a   b   c   d   e   f   g   h\n  +---+---+---+---+---+---+---+---+\n";
    for (int r = 0; r < 8; r++) {
        cout << (8 - r) << " |";
        for (int c = 0; c < 8; c++) {
            if (grid[r][c] == nullptr) cout << " . |";
            else cout << " " << grid[r][c]->getSymbol() << " |";
        }
        cout << " " << (8 - r) << "\n  +---+---+---+---+---+---+---+---+\n";
    }
    cout << "    a   b   c   d   e   f   g   h\n\n";
}

Piece* Board::getPiece(int r, int c) { return grid[r][c]; }

bool Board::movePiece(int fromRow, int fromCol, int toRow, int toCol) {
    Piece* piece = grid[fromRow][fromCol];
    if (!piece->isValidMove(fromRow, fromCol, toRow, toCol, grid)) return false;
    if (grid[toRow][toCol] != nullptr) {
        delete grid[toRow][toCol];
    }
    grid[toRow][toCol] = piece;
    grid[fromRow][fromCol] = nullptr;
    return true;
}

bool Board::kingAlive(int color) {
    char kingChar = (color == WHITE) ? 'K' : 'k';
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            if (grid[r][c] != nullptr && grid[r][c]->getSymbol() == kingChar) return true;
    return false;
}

Board::~Board() {
    for (int r = 0; r < 8; r++) for (int c = 0; c < 8; c++) delete grid[r][c];
}

// --- Game Implementation ---
Game::Game() : currentTurn(WHITE) {}
int Game::colToIndex(char c) { return c - 'a'; }
int Game::rowToIndex(int r) { return 8 - r; }

void Game::run() {
    while (true) {
        board.display();
        cout << "  >>> " << (currentTurn == WHITE ? "WHITE" : "BLACK") << "'s turn\n  Enter move (e.g. e2 e4): ";
        string input; getline(cin, input);
        if (input == "quit") break;
        if (input.size() < 5) continue;

        int fC = colToIndex(input[0]), fR = rowToIndex(input[1] - '0');
        int tC = colToIndex(input[3]), tR = rowToIndex(input[4] - '0');

        Piece* p = board.getPiece(fR, fC);
        if (p == nullptr || p->getColor() != currentTurn) {
            cout << "  [!] Invalid selection!\n";
            continue;
        }

        if (board.movePiece(fR, fC, tR, tC)) {
            if (!board.kingAlive(currentTurn == WHITE ? BLACK : WHITE)) {
                board.display();
                cout << "  *** CHECKMATE! ***\n";
                break;
            }
            currentTurn = (currentTurn == WHITE) ? BLACK : WHITE;
        }
        else {
            cout << "  [!] Invalid move!\n";
        }
    }
}
#ifndef CHESS_H_
#define CHESS_H_

#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//using std::cin, std::cout, std::endl, std::string, std::map, std::unordered_map, std::ostream, std::vector, std::istream,
//std::ios_base;
using namespace std;

class Move;
class Board;

class Piece {
public:
    bool white; // True for white, False for black
    char type;  // 'p' pawn, 'b' bishop, 'n' for knight
    // 'r' for rook, 'q' for queen, 'k' for king

    // constructor
    Piece(char t, bool w) {
        type = t;
        white = w;
    }

    // print the piece
    // note: upper case for white, lower case for black
    friend ostream& operator<<(ostream& os, const Piece& p) {
        if (p.white) os << (char)toupper(p.type);
        else os << (char)tolower(p.type);
        return os;
    }

    // virtual function 
    virtual bool legal_move(const Board* b, const Move* m);
    //bool is_legal(however they want to move);
};

class Pawn : public Piece {
public:
    Pawn(bool white) : Piece('p', white) {
    }

    //bool is_legal(however they want to move);
};

class Bishop : public Piece {
public:
    Bishop(bool white) : Piece('b', white) {
    }

    //bool is_legal(however they want to move);
    bool legal_move(const Board* b, const Move* m);
};


class Knight : public Piece {
public:
    Knight(bool white) : Piece('n', white) {
    }

    //bool is_legal(however they want to move);
    bool legal_move(const Board* b, const Move* m);
};

// h6
// - add Rook, 'r' (aka castle)
// - add Queen, 'q'
// - add King, 'k'

// h6, add legal_move methods for: Rook, King, Queen, Knight

// h6 - note that we are /not/ checking the following rules yet...
//    - legal move for pawns
//    - for bishops/rooks/queens, make sure not jumping over any pieces
//    - checking for checks and checkmates

class Rook : public Piece {
public:
    Rook(bool white) : Piece('r', white) {
    }

    //bool is_legal(however they want to move);
    bool legal_move(const Board* b, const Move* m);

    bool _do_move(const Board* b, const Move* m);
};

class Queen : public Piece {
public:
    Queen(bool white) : Piece('q', white) {
    }

    //bool is_legal(however they want to move);
    bool legal_move(const Board* b, const Move* m);
};

class King : public Piece {
public:
    King(bool white) : Piece('k', white) {
    }

    //bool is_legal(however they want to move);
    bool legal_move(const Board* b, const Move* m);
};


class Square {
public:
    Piece* p;
    bool white;
    int rank;  // row
    char file; // column

    Square(bool w, int r, char f) {
        p = NULL;
        white = w;
        rank = r;
        file = f;
    }

    friend ostream& operator<<(ostream& os, const Square& s) {
        if (s.p != NULL) os << *s.p;
        else {
            // otherwise, checkerboard of '-' and ' '
            // h6 - '.' instead of '-'
            if ((s.rank - 1 + s.file - 'a') % 2 == 0)
                os << '.';
            else
                os << ' ';
        }
        return os;
    }
};

class Move;

class Board {
public:
    vector<Square> b;
    bool white_to_move;

    Board();

    friend ostream& operator<<(ostream& os, const Board& b);
    unsigned int which_index(char file, unsigned int rank) const;
    // make this work like [], but [] can't take two arguments
    Square& operator()(char file, unsigned int rank);

    // game_over()
    bool game_over();

    void do_move(Move* m);
};


class Game {
public:
};

class Position {
public:
    char file; // column, a-h
    int rank;  // row,    1-8
    friend istream& operator>>(istream& is, Position& p);
    bool valid_coords() const {
        if (file < 'a' || file > 'h') return false;
        if (rank < 1 || rank > 8) return false;
        return true;
    }
};

class Move {
public:
    Position from, to;

    // where from

    // where to

    // which player (black, white)

    // operator>>()
    friend istream& operator>>(istream& is, Move& m);

    // is_legal()
    bool is_legal(const Board b);
};

#endif

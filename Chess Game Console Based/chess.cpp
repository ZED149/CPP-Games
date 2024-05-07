/*
 */

#include "chess.h"
#include <Windows.h>

int main(int argc, char* argv[]) {

    // declare a new chess game/board
    Board b; // creates the squares, puts white and black pieces
    Move m;
    auto legal_move_flag = false;

    // while game not done
    bool quit = false;
    do {
        // print the board
        cout << b << endl;

        // get their move
        //Move m;
        do {
            // h6 - let them know to type q1 q2 to quit
            cout << "(To quit, type q1 q2 and enter or return.)" << endl;

            cout << "Input move in chess notation (e.g., e2 e4): ";
            cin >> m;

            // h6 - check if they wanted to quit (if the file of the from or to is 'q')
            //      if so break and set a flag that can be checked as well (since we
            //      need to break out of this do/while loop and the loop outside of this
            //      one as well).
            if (m.from.file == 'q' && m.from.rank == 1 &&
                m.to.file == 'q' && m.to.rank == 2) {
                quit = true;
                break;
            }

            // check that it is a legal move
            legal_move_flag = !m.is_legal(b);
            if (legal_move_flag) {
                cout << "Not legal. Try again." << endl;
            }
        } while (legal_move_flag);

        // h6 - check flag whether they want to quit
        if (quit) break;

        // do the move
        b.do_move(&m);

        // is the game over?
    } while (!b.game_over());

}


Board::Board() {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            b.push_back(Square((row + col) % 2 == 1, col + 'a', 8 - row));
        }
    }
    // note: new instead of malloc

    // white
    for (char r = 'a'; r <= 'h'; r++)
        operator()(r, 2).p = new Pawn(true);

    operator()('c', 1).p = new Bishop(true);
    operator()('f', 1).p = new Bishop(true);

    operator()('b', 1).p = new Knight(true);
    operator()('g', 1).p = new Knight(true);

    // h6 - add rooks (R), queens (Q), kings (K)
    //      need to add classes for those in chess.h and
    //      add new ones here
    // Note positions of queen/king
    //      white queen on d1, white king on e1
    //      black queen on d8, black king on e8

    operator()('a', 1).p = new Rook(true);
    operator()('h', 1).p = new Rook(true);

    operator()('d', 1).p = new Queen(true);
    operator()('e', 1).p = new King(true);


    // black
    for (char r = 'a'; r <= 'h'; r++)
        operator()(r, 7).p = new Pawn(false);

    operator()('c', 8).p = new Bishop(false);
    operator()('f', 8).p = new Bishop(false);

    operator()('b', 8).p = new Knight(false);
    operator()('g', 8).p = new Knight(false);

    operator()('a', 8).p = new Rook(false);
    operator()('h', 8).p = new Rook(false);

    operator()('d', 8).p = new Queen(false);
    operator()('e', 8).p = new King(false);

    white_to_move = true;
}

ostream& operator<<(ostream& os, const Board& b) {

    // h6 - update the printing so it looks a little nicer

    os << "  a b c d e f g h " << endl;
    os << " -----------------" << endl;
    for (unsigned int i = 0; i < b.b.size(); i++) {
        if (i % 8 == 0) {
            // printing the left |
            os << (64 - i) / 8 << '|';
        }
        os << b.b[i];
        os << '|';
        if (i % 8 == 7) {
            // printing end of the line
            os << (64 - (i - 7)) / 8 << endl;
            if (i < b.b.size() - 1)
                os << "  - - - - - - - -  " << endl;
        }
    }
    os << " -----------------" << endl;
    os << "  a b c d e f g h " << endl;
    if (b.white_to_move)
        os << "   white to move" << endl;
    else
        os << "   black to move" << endl;
    return os;
}

unsigned int Board::which_index(char file, unsigned int rank) const {
    return (8 - rank) * 8 + (file - 'a');
}

// make this work like [], because [] can't take two arguments
Square& Board::operator()(char file, unsigned int rank) {
    return b[which_index(file, rank)];
}


bool Board::game_over() {
    return false;
}

void Board::do_move(Move* m) {
    int from_i = which_index(m->from.file, m->from.rank);
    int to_i = which_index(m->to.file, m->to.rank);

    // check if its a pawn
    if (b[from_i].p->type == 'p')
    {
        // check if its a white piece
        if (b[from_i].p->white)
        {
            // yes it is
            // check its rank of destination
            if (m->to.rank == 8)
            {
                // ask user
                char what = ' ';
                cout << "Your pawn is being promoted. Do you want a (q)ueen, (r)ook, (b)ishop, or k(n)ight?" << endl;
                cin >> what;
                switch (what)
                {
                case 'q':
                    // delete from and put new piece there
                    delete b[from_i].p;
                    b[from_i].p = new Queen(true);
                    break;
                case 'r':
                    // delete from and put new piece there
                    delete b[from_i].p;
                    b[from_i].p = new Rook(true);
                    break;
                case 'b':
                    // delete from and put new piece there
                    delete b[from_i].p;
                    b[from_i].p = new Bishop(true);
                    break;
                case 'n':
                    // delete from and put new piece there
                    delete b[from_i].p;
                    b[from_i].p = new Knight(true);
                    break;
                }
            }
        }
        else
        {
            // no it isn't
            // check its rank of destination
            // ask user
            char what = ' ';
            cout << "Your pawn is being promoted. Do you want a (q)ueen, (r)ook, (b)ishop, or k(n)ight?" << endl;
            cin >> what;
            switch (what)
            {
            case 'q':
                // delete from and put new piece there
                delete b[from_i].p;
                b[from_i].p = new Queen(true);
                break;
            case 'r':
                // delete from and put new piece there
                delete b[from_i].p;
                b[from_i].p = new Rook(true);
                break;
            case 'b':
                // delete from and put new piece there
                delete b[from_i].p;
                b[from_i].p = new Bishop(true);
                break;
            case 'n':
                // delete from and put new piece there
                delete b[from_i].p;
                b[from_i].p = new Knight(true);
                break;
            }
        }
    }

    // check for castling corrdintes
    bool castling_flag = false;
    if (m->from.file == 'e' && m->from.rank == 1)
    {
        castling_flag = true;
        // for white king
        // check for to coordintates
        if (m->to.file == 'g' && m->to.rank == 1)
        {
            // moving right
            b[63].p = NULL;
            b[61].p = new Rook(true);
            delete b[from_i].p;
            b[from_i].p = NULL;
            b[to_i].p = new King(true);
        }
        else if (m->to.file == 'c' && m->to.rank == 1)
        {
            // moving left
            b[56].p = NULL;
            b[57].p = new Rook(true);
            delete b[from_i].p;
            b[from_i].p = NULL;
            b[to_i].p = new King(true);
        }
    }
    else if (m->from.file == 'e' && m->from.rank == 8)
    {
        castling_flag = true;
        // for black king
        // check for to coordintates
        if (m->to.file == 'g' && m->to.rank == 8)
        {
            // moving right
            b[7].p = NULL;
            b[5].p = new Rook(false);
            delete b[from_i].p;
            b[from_i].p = NULL;
            b[to_i].p = new King(false);
        }
        else if (m->to.file == 'c' && m->to.rank == 8)
        {
            // moving left
            b[0].p = NULL;
            b[1].p = new Rook(false);
            delete b[from_i].p;
            b[from_i].p = NULL;
            b[to_i].p = new King(false);
        }
    }

    if (!castling_flag)
    {
        // h7 - make sure to delete a piece if being removed
        if (b[to_i].p != NULL)
            delete b[to_i].p;

        // put piece from from_i to to_i
        b[to_i].p = b[from_i].p;

        b[from_i].p = NULL;

        white_to_move = !(white_to_move);
    }
}


// note that Move & m, means that m is "pass by reference"
istream& operator>>(istream& is, Move& m) {
    // h6 - if they want to quit, they can type quit. don't need
    //      to do anything with that here, just check it in main
    is >> m.from >> m.to;
    return is;
}

istream& operator>>(istream& is, Position& p) {
    string s;
    is >> s; // s should be something like "a1" or "h7"
    // h6 - note that if they don't type something in that we expect
    //      probably we won't crash, but the file and rank will be
    //      stange values, so just make sure this doesn't break
    //      other parts of the code.  
    p.file = s[0];
    p.rank = s[1] - '0';
    return is;
}

bool Move::is_legal(const Board b) {
    // things to check...
    int from_i = b.which_index(from.file, from.rank);
    int to_i = b.which_index(to.file, to.rank);

    // check for castling coordintes here
    if (from.file == 'e' && from.rank == 1)
    {
        // for white king
        // check for to coordintates
        if (to.file == 'g' && to.rank == 1)
        {
            b.b[from_i].p->legal_move(&b, this);
            return true;
        }
        else if (to.file == 'c' && to.rank == 1)
        {
            b.b[from_i].p->legal_move(&b, this);
            return true;
        }
    }
    else if (from.file == 'e' && from.rank == 8)
    {
        // for black king
        // check for to coordintates
        if (to.file == 'g' && to.rank == 8)
        {
            b.b[from_i].p->legal_move(&b, this);
            return true;
        }
        else if (to.file == 'c' && to.rank == 8)
        {
            b.b[from_i].p->legal_move(&b, this);
            return true;
        }
    }

    // check that there is a piece on that square
    if (b.b[from_i].p == NULL) return false;

    // check that we're moving the right player's piece
    if (b.white_to_move != b.b[from_i].p->white) {
        return false;
    }

    // h6 - if trying to capture their own piece, not a legal move
    //    - need to look up if there is a piece on the from and to squares
    //      and if they have the same value for white
    if (b.b[to_i].p != NULL &&
        b.b[from_i].p->white == b.b[to_i].p->white)
        return false;

    // given the piece being moved and the board, is it legal
    if (!b.b[from_i].p->legal_move(&b, this))
        return false;

    // checks for pawn
    if (b.b[from_i].p->type == 'p')
    {
        // if its a pawn
        // check for its rank difference
        if (to_i > from_i)
        {
            // if pawn is moving downwards
            if ((to_i - from_i) > 16)
                return false;
        }
        else if (from_i > to_i)
        {
            // pawn is moving topwards
            if ((from_i - to_i) > 16)
                return false;
        }
    }

    return true;
}


bool Piece::legal_move(const Board* b, const Move* m) {
    if (b == NULL || m == NULL) return false;

    // if it's not valid coordinates, then not a legal move
    if (!m->from.valid_coords() ||
        !m->to.valid_coords()) return false;

    // h6 - if the from and to coordinates are the same, not a legal move
    if (m->from.file == m->to.file &&
        m->from.rank == m->to.rank) return false;

    return true;
}

// done
bool Bishop::legal_move(const Board* b, const Move* m) {
    // call the generic function, and make sure it passes
    if (!Piece::legal_move(b, m)) return false;

    // checking how the bishop moves
    if (abs(m->from.file - m->to.file) !=
        abs(m->from.rank - m->to.rank)) return false;

    // my code from here
    return Bishop::_do_move(b, m);
}

// implementation of Bishop legal move
bool Bishop::_do_move(const Board* b, const Move* m)
{
    // Now, the col or row to be moved is correct.
    // We will check if there is any other piece in the path or not
    // if there is a piece in the path and its not the same colour
    // we need to remove it from the board
    // checking for any piece in the path
    int r = 0;
    switch (m->from.rank)
    {
    case 1:
        r = 8 * 7;
        break;
    case 2:
        r = 8 * 6;
        break;
    case 3:
        r = 8 * 5;
        break;
    case 4:
        r = 8 * 4;
        break;
    case 5:
        r = 8 * 3;
        break;
    case 6:
        r = 8 * 2;
        break;
    case 7:
        r = 8 * 1;
        break;
    case 8:
        r = 8 * 0;
        break;
    }
    int index = (r)+(m->from.file - 96) - (1);
    switch (m->to.rank)
    {
    case 1:
        r = 8 * 7;
        break;
    case 2:
        r = 8 * 6;
        break;
    case 3:
        r = 8 * 5;
        break;
    case 4:
        r = 8 * 4;
        break;
    case 5:
        r = 8 * 3;
        break;
    case 6:
        r = 8 * 2;
        break;
    case 7:
        r = 8 * 1;
        break;
    case 8:
        r = 8 * 0;
        break;
    }
    int end = (r)+(m->to.file - 96) - (1);

    if (m->from.rank < m->to.rank)
    {
        // if bishop is moving in updwards
        if (m->from.file < m->to.file)
        {
            // if the bishop is moving in up-right direction
            for (int i = (index - 7); i >= end; i -= 7)
            {

                if (b->b[i].p)
                {
                    if (b->b[i].p->white == b->b[index].p->white)
                    {
                        // if the two pieces are same
                        return false;
                    }
                    if ((b->b[i].p->white != b->b[index].p->white) && i == end)
                    {
                        // if pieces are not the same and this is the end location of the Rook
                        // remove piece and return
                        //delete b->b[i].p;
                        return true;
                    }
                    if ((b->b[i].p->white != b->b[index].p->white) && i != end)
                    {
                        // if pieces are not the same and this is not the end location of the Rook
                        // remove piece and return
                        return false;
                    }
                }
                else
                {
                    // if there is not any piece
                    if (i == end)
                    {
                        // if i is equal to end, it means that we need to place Rook here
                        // and return true
                        return true;
                    }
                }
            }
            // this will return false for error handling purpose.
            return false;
        }
        else if (m->from.file > m->to.file)
        {
            // if the bishop is moving in up-left direction
            for (int i = (index - 9); i >= end; i -= 9)
            {
                if (b->b[i].p)
                {
                    if (b->b[i].p->white == b->b[index].p->white)
                    {
                        // if the two pieces are same
                        return false;
                    }
                    if ((b->b[i].p->white != b->b[index].p->white) && i == end)
                    {
                        // if pieces are not the same and this is the end location of the Rook
                        // remove piece and return
                        //delete b->b[i].p;
                        return true;
                    }
                    if ((b->b[i].p->white != b->b[index].p->white) && i != end)
                    {
                        // if pieces are not the same and this is not the end location of the Rook
                        // remove piece and return
                        return false;
                    }
                }
                else
                {
                    // if there is not any piece
                    if (i == end)
                    {
                        // if i is equal to end, it means that we need to place Rook here
                        // and return true
                        return true;
                    }
                }
            }
            // this will return false for error handling purpose.
            return false;
        }
    }
    else if (m->from.rank > m->to.rank)
    {
        // if the bishop is moving downwards
        if (m->from.file < m->to.file)
        {
            // if the bishop is moving in down-right direction
            for (int i = (index + 9); i <= end; i += 9)
            {
                if (b->b[i].p)
                {
                    if (b->b[i].p->white == b->b[index].p->white)
                    {
                        // if the two pieces are same
                        return false;
                    }
                    if ((b->b[i].p->white != b->b[index].p->white) && i == end)
                    {
                        // if pieces are not the same and this is the end location of the Rook
                        // remove piece and return
                        //delete b->b[i].p;
                        return true;
                    }
                    if ((b->b[i].p->white != b->b[index].p->white) && i != end)
                    {
                        // if pieces are not the same and this is not the end location of the Rook
                        // remove piece and return
                        return false;
                    }
                }
                else
                {
                    // if there is not any piece
                    if (i == end)
                    {
                        // if i is equal to end, it means that we need to place Rook here
                        // and return true
                        return true;
                    }
                }
            }
            // this will return false for error handling purpose.
            return false;
        }
        else if (m->from.file > m->to.file)
        {
            // if the bishop is moving in down-left direction
            for (int i = (index + 7); i <= end; i += 7)
            {
                if (b->b[i].p)
                {
                    if (b->b[i].p->white == b->b[index].p->white)
                    {
                        // if the two pieces are same
                        return false;
                    }
                    if ((b->b[i].p->white != b->b[index].p->white) && i == end)
                    {
                        // if pieces are not the same and this is the end location of the Rook
                        // remove piece and return
                        //delete b->b[i].p;
                        return true;
                    }
                    if ((b->b[i].p->white != b->b[index].p->white) && i != end)
                    {
                        // if pieces are not the same and this is not the end location of the Rook
                        // remove piece and return
                        return false;
                    }
                }
                else
                {
                    // if there is not any piece
                    if (i == end)
                    {
                        // if i is equal to end, it means that we need to place Rook here
                        // and return true
                        return true;
                    }
                }
            }
            // this will return false for error handling purpose.
            return false;
        }
    }
}

// h6 - add legal_move methods for: rook, king, queen, knight

// done
bool Rook::legal_move(const Board* b, const Move* m) {
    // call the generic function, and make sure it passes
    if (!Piece::legal_move(b, m)) return false;

    
    // checking how the rook moves
    if (m->from.file - m->to.file != 0 &&
        m->from.rank - m->to.rank != 0) return false;
    
    // my code from here
    return Rook::_do_move(b, m);
}

// implementation of Rook legal move
bool Rook::_do_move(const Board* b, const Move* m)
{
    // Now, the col or row to be moved is correct.
    // We will check if there is any other piece in the path or not
    // if there is a piece in the path and its not the same colour
    // we need to remove it from the board
    // checking for any piece in the path    
    if (m->from.file == m->to.file)
    {
        // if rook is moving in col direction (vertically)
        int r = 0;
        switch (m->from.rank)
        {
        case 1:
            r = 8 * 7;
            break;
        case 2:
            r = 8 * 6;
            break;
        case 3:
            r = 8 * 5;
            break;
        case 4:
            r = 8 * 4;
            break;
        case 5:
            r = 8 * 3;
            break;
        case 6:
            r = 8 * 2;
            break;
        case 7:
            r = 8 * 1;
            break;
        case 8:
            r = 8 * 0;
            break;
        }
        int index = (r)+(m->from.file - 96) - (1);
        switch (m->to.rank)
        {
        case 1:
            r = 8 * 7;
            break;
        case 2:
            r = 8 * 6;
            break;
        case 3:
            r = 8 * 5;
            break;
        case 4:
            r = 8 * 4;
            break;
        case 5:
            r = 8 * 3;
            break;
        case 6:
            r = 8 * 2;
            break;
        case 7:
            r = 8 * 1;
            break;
        case 8:
            r = 8 * 0;
            break;
        }
        int end = (r)+(m->to.file - 96) - (1);
        if (m->from.rank < m->to.rank)
        {
            // moving updwards
            for (int i = index - 8; i >= end; i -= 8)
            {
                if (b->b[i].p)
                {
                    if (b->b[i].p->white == b->b[index].p->white)
                    {
                        // if the two pieces are same
                        return false;
                    }
                    if ((b->b[i].p->white != b->b[index].p->white) && i == end)
                    {
                        // if pieces are not the same and this is the end location of the Rook
                        // remove piece and return
                        //delete b->b[i].p;
                        return true;
                    }
                    if ((b->b[i].p->white != b->b[index].p->white) && i != end)
                    {
                        // if pieces are not the same and this is not the end location of the Rook
                        // remove piece and return
                        return false;
                    }
                }
                else
                {
                    // if there is not any piece
                    if (i == end)
                    {
                        // if i is equal to end, it means that we need to place Rook here
                        // and return true
                        return true;
                    }
                }
            }
            // this will return false for error handling purpose.
            return false;
        }
        else if (m->from.rank > m->to.rank)
        {
            // moving downwards
            for (int i = index + 8; i <= end; i += 8)
            {
                if (b->b[i].p)
                {
                    if (b->b[i].p->white == b->b[index].p->white)
                    {
                        // if the two pieces are same
                        return false;
                    }
                    if ((b->b[i].p->white != b->b[index].p->white) && i == end)
                    {
                        // if pieces are not the same and this is the end location of the Rook
                        // remove piece and return
                        //delete b->b[i].p;
                        return true;
                    }
                    if ((b->b[i].p->white != b->b[index].p->white) && i != end)
                    {
                        // if pieces are not the same and this is not the end location of the Rook
                        // remove piece and return
                        return false;
                    }
                }
                else
                {
                    // if there is not any piece
                    if (i == end)
                    {
                        // if i is equal to end, it means that we need to place Rook here
                        // and return true
                        return true;
                    }
                }
            }
            // this will execute for error handling purposes.
            return false;
        }
    }
    else if (m->from.rank == m->to.rank)
    {
        // if rook is moving in row direction (horizontally)
        int r = 0;
        switch (m->from.rank)
        {
        case 1:
            r = 8 * 7;
            break;
        case 2:
            r = 8 * 6;
            break;
        case 3:
            r = 8 * 5;
            break;
        case 4:
            r = 8 * 4;
            break;
        case 5:
            r = 8 * 3;
            break;
        case 6:
            r = 8 * 2;
            break;
        case 7:
            r = 8 * 1;
            break;
        case 8:
            r = 8 * 0;
            break;
        }
        int index = (r)+(m->from.file - 96) - (1);
        switch (m->to.rank)
        {
        case 1:
            r = 8 * 7;
            break;
        case 2:
            r = 8 * 6;
            break;
        case 3:
            r = 8 * 5;
            break;
        case 4:
            r = 8 * 4;
            break;
        case 5:
            r = 8 * 3;
            break;
        case 6:
            r = 8 * 2;
            break;
        case 7:
            r = 8 * 1;
            break;
        case 8:
            r = 8 * 0;
            break;
        }
        int end = (r)+(m->to.file - 96) - (1);
        if (m->from.file < m->to.file)
        {
            // moving right
            for (int i = index + 1; i <= end; i++)
            {
                if (b->b[i].p)
                {
                    if (b->b[i].p->white == b->b[index].p->white)
                    {
                        // if the two pieces are same
                        return false;
                    }
                    if ((b->b[i].p->white != b->b[index].p->white) && i == end)
                    {
                        // if pieces are not the same and this is the end location of the Rook
                        // remove piece and return
                        delete b->b[i].p;
                        return true;
                    }
                    if ((b->b[i].p->white != b->b[index].p->white) && i != end)
                    {
                        // if pieces are not the same and this is not the end location of the Rook
                        // remove piece and return
                        return false;
                    }
                }
                else
                {
                    // if there is not any piece
                    if (i == end)
                    {
                        // if i is equal to end, it means that we need to place Rook here
                        // and return true
                        return true;
                    }
                }
            }
            // this will return false for error handling purpose.
            return false;
        }
        else if (m->from.file > m->to.file)
        {
            // moving left
            for (int i = index - 1; i >= end; i--)
            {
                if (b->b[i].p)
                {
                    if (b->b[i].p->white == b->b[index].p->white)
                    {
                        // if the two pieces are same
                        return false;
                    }
                    if ((b->b[i].p->white != b->b[index].p->white) && i == end)
                    {
                        // if pieces are not the same and this is the end location of the Rook
                        // remove piece and return
                        delete b->b[i].p;
                        return true;
                    }
                    if ((b->b[i].p->white != b->b[index].p->white) && i != end)
                    {
                        // if pieces are not the same and this is not the end location of the Rook
                        // remove piece and return
                        return false;
                    }
                }
                else
                {
                    // if there is not any piece
                    if (i == end)
                    {
                        // if i is equal to end, it means that we need to place Rook here
                        // and return true
                        return true;
                    }
                }
            }
            // this will execute for error handling purposes.
            return false;
        }
    }
}

bool King::legal_move(const Board* b, const Move* m) {
    // call the generic function, and make sure it passes
    if (!Piece::legal_move(b, m)) return false;

    //// checking how the king moves
    //if (abs(m->from.file - m->to.file) > 1 ||
    //    abs(m->from.rank - m->to.rank) > 1) return false;

    // my code from here
    int r = 0;
    switch (m->from.rank)
    {
    case 1:
        r = 8 * 7;
        break;
    case 2:
        r = 8 * 6;
        break;
    case 3:
        r = 8 * 5;
        break;
    case 4:
        r = 8 * 4;
        break;
    case 5:
        r = 8 * 3;
        break;
    case 6:
        r = 8 * 2;
        break;
    case 7:
        r = 8 * 1;
        break;
    case 8:
        r = 8 * 0;
        break;
    }
    int index = (r)+(m->from.file - 96) - (1);
    switch (m->to.rank)
    {
    case 1:
        r = 8 * 7;
        break;
    case 2:
        r = 8 * 6;
        break;
    case 3:
        r = 8 * 5;
        break;
    case 4:
        r = 8 * 4;
        break;
    case 5:
        r = 8 * 3;
        break;
    case 6:
        r = 8 * 2;
        break;
    case 7:
        r = 8 * 1;
        break;
    case 8:
        r = 8 * 0;
        break;
    }
    int end = (r)+(m->to.file - 96) - (1);
    // perform castling
    // check piece color
    if (b->b[index].p->white)
    {
        // if its a white king
        // check if white king is on e1
        if (m->from.file == 'e' && m->from.rank == 1)
        {
            if (m->to.file == 'g')
            {
                // castling towards right
                // move night to the side of king (left) one square
                if (b->b[61].p)
                {
                    // if a piece is already present there
                    // delete rook from its place and the piece also
                    // move rook to the side of the king
                    // deleteing rook
                    delete b->b[63].p;
                    // deleting piece
                    delete b->b[61].p;
                    return true;
                }
                else
                {
                    // delete rook only
                    delete b->b[63].p;
                    return true;
                }
            }
            else if (m->to.file == 'c')
            {
                // castling towards left
                // move night to the side of king (right) one square
                if (b->b[58].p)
                {
                    // if a piece is already present there
                    // delete rook from its place and the piece also
                    // move rook to the side of the king
                    // deleteing rook
                    delete b->b[56].p;
                    // deleting piece
                    delete b->b[58].p;
                    return true;
                }
                else
                {
                    // delete rook only
                    delete b->b[56].p;
                    return true;
                }
            }
        }
        else
            return false;
    }
    else if (b->b[index].p->white == false)
    {
        // if its a black king
        // if its a white king
        // check if white king is on e1
        if (m->from.file == 'e' && m->from.rank == 8)
        {
            if (m->to.file == 'g')
            {
                // castling towards right
                // move night to the side of king (left) one square
                if (b->b[5].p)
                {
                    // if a piece is already present there
                    // delete rook from its place and the piece also
                    // move rook to the side of the king
                    // deleteing rook
                    delete b->b[7].p;
                    // deleting piece
                    delete b->b[5].p;
                    return true;
                }
                else
                {
                    // delete rook only
                    delete b->b[7].p;
                    return true;
                }
            }
            else if (m->to.file == 'c')
            {
                // castling towards left
                // move night to the side of king (right) one square
                if (b->b[2].p)
                {
                    // if a piece is already present there
                    // delete rook from its place and the piece also
                    // move rook to the side of the king
                    // deleteing rook
                    delete b->b[0].p;
                    // deleting piece
                    delete b->b[2].p;
                    return true;
                }
                else
                {
                    // delete rook only
                    delete b->b[0].p;
                    return true;
                }
            }
        }
        else
            return false;
    }

    return true;
}

// done
bool Queen::legal_move(const Board* b, const Move* m) {
    // call the generic function, and make sure it passes
    if (!Piece::legal_move(b, m)) return false;

    // checking how the queen moves
    if (
        (m->from.file - m->to.file != 0 &&  // rook-style move
            m->from.rank - m->to.rank != 0) &&

        (abs(m->from.file - m->to.file) !=
            abs(m->from.rank - m->to.rank)) // bishop-style move
        ) return false;

    // my code from here
    // Queen can move in total of 8 directions
    // We have already implemented those directions in cases of 
    // Bishop and Rook
    // We just need to call those functions with proper params to execute them as queen

    // check in which direction queen is moving and then call the exact method
    if (m->from.file == m->to.file)
    {
        // if queen is moving upwards (vertically)
        // it means queen is moving like a Rook
        return Rook::_do_move(b, m);
    }
    else if (m->from.rank == m->to.rank)
    {
        // if queen is moving rowwise horizontally 
        // it means queen is moving like a Rook
        return Rook::_do_move(b, m);
    }
    else if (m->from.rank < m->to.rank)
    {
        // if queen is moving upwards (diagonally)
        // it means queen is moving like a Bishop
        return Bishop::_do_move(b, m);
    }
    else if (m->from.rank > m->to.rank)
    {
        // if queen is moving downwards (diagonally)
        // it means queen is moving like a Bishop
        return Bishop::_do_move(b, m);
    }
}

bool Knight::legal_move(const Board* b, const Move* m) {
    // call the generic function, and make sure it passes
    if (!Piece::legal_move(b, m)) return false;

    // checking how the knight moves
    if (!(abs(m->from.file - m->to.file) == 1 &&
        abs(m->from.rank - m->to.rank) == 2) &&
        !(abs(m->from.file - m->to.file) == 2 &&
            abs(m->from.rank - m->to.rank) == 1))
        return false;

    return true;
}


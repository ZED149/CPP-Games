The cpp/h files in this directory are Jeff's solution for h6.
You can start with these, or copy over your files if you got
everything right on h6.

Things we will add for h7 (and how many points...)
* (5 points) legal_move for rook, bishop, queen - make it so they cannot jump over pieces.
* (5 points) castling - can move king to 'g' or 'c' ranks, and will also move the knight in that direction to the square next to the king
  - update legal move for king to allow the castle move (if white king is on e1, can move to c1 or g1; if black king is on e8, can move to c8 or g8).
  - update do_move to check if this is a castle move, and move the rook as well.
  - optional (ungraded) - checking that the castling is legal (not starting from check, moving through check, ending up in check, and needs to be king's first move).
* (5 points) pawn promotion
  - if black pawn is moving to rank 1, or white pawn is moving to rank 8, do_move should do pawn promotion. Transcript should look like this:
    Your pawn is being promoted. Do you want a (q)ueen, (r)ook, (b)ishop, or k(n)ight: __q__
  depending on what they type, create a new piece, put it there instead of the pawn, delete the pawn.
* if removing a piece, delete it
  - in do_move, if there was a piece that is being captured,
     delete b[to_i].p;

Optional (not graded) - 
* pawn legal
  - if square "in front" of the pawn is empty, can move forward"
  - if square diagonally "in front" of the pawn is the opponent, can capture
  - first move, pawn can move forward 2 spots (only if these two spots are empty).
  - if pawn makes it all the way to the other side, gets promoted (player chooses Q, B, R, N).
  - en passant - if opposing pawn just moved 2 spots and your pawn is on the same rank (row), you can capture by going to the square the opposing pawn just skipped over.
* check and checkmate
* any other rules

Updated notes (5/2)
* delete - to get rid of compile warning, needed to add virtual destructors for all of the classes. also fixed the snippet of code that I had put in for the delete.
* legal_move checks for rook/bishop/queen - add this in the is_legal method for Move (since you'll need the board to determine if a piece is in the way)
* castling - add a check for this in the King's legal_move, then update do_move to move the Rook as well.
* see lecture on 5/3 for more details.

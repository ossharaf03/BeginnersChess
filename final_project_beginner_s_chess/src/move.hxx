#pragma once
#include "player.hxx"
#include "model.hxx"
#include "board.hxx"
#include <ge211.hxx>
#include <algorithm>

class Move
{
public:

    using Move_Vector = std::vector<std::vector<int>>;
    //evaluates if a given position is in the bounds of the board
    bool good_pos (int, int);
    //evaluates if a given position is viable specifically for knights
    bool knight_good_pos (int, int);
    //
    explicit Move(Model const&);
    // checks if a given move is viable for a given piece and executes a move
    // if it is
    void execute_move(int, int, int, int);

    //edits a vector of vectors containing possible spaces a piece can move
    // in a certain direction
    void find_moves
    (Move_Vector, int, int, Board::Position);

    //returns a vector of vectors containing all the possible moves a piece
    // can make
    Move_Vector rook_moves(int, int);
    Move_Vector bishop_moves(int, int);
    Move_Vector queen_moves(int, int);
    Move_Vector knight_moves(int, int);
    Move_Vector pawn_moves(int, int);
    Move_Vector king_moves(int, int);


private:
    Model const& model_;
    std::vector<Board::Position> straight_dir();
    std::vector<Board::Position> diagonal_dir();

};


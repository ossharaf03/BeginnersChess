#pragma once

#include "model.hxx"
#include <algorithm>
#include <ge211.hxx>
#include "player.hxx"
#include "board.hxx"

class Square
{
private:
    Piece piece_;
    Color color_;

public:
    //construct Square
    Square();

    //returns piece name
    Piece getPiece();

    //returns color of piece
    Color getColor();

    //set piece and color
    void setPandC(Piece, Color);

    //sets a position on the board to a certain player
    void setSpace(Square);

    //sets a position on the board to empty
    void setEmpty();
};

class Model
{
public:
    Model();
    const int grid_size = 8;

    // getter function for square
    Square square_at(int i, int j) const;
    Color other_player() const;
    void switch_turn();
    Color get_turn() const;

    using Move_Vector = std::vector<std::vector<int>>;
    //evaluates if a given position is in the bounds of the board

    //
    // MOVE FUNCTIONS
    //

    bool good_pos (int, int);
    //evaluates if a given position is viable specifically for knights
    bool knight_good_pos (int, int);

    // checks if a given move is viable for a given piece and executes a move
    // if it is
    void execute_move(int, int, int, int);

    //edits a vector of vectors containing possible spaces a piece can move
    // in a certain direction
    void find_moves
            (int, int, Board::Position);

    //returns a vector of vectors containing all the possible moves a piece
    // can make
    void rook_moves(int, int);
    void bishop_moves(int, int);
    void queen_moves(int, int);
    void knight_moves(int, int);
    void pawn_moves(int, int);
    void king_moves(int, int);

    //
    // Player functions
    //

    //set piece and color
    void setPandC(int, int, Piece, Color);

    //sets a position on the board to a certain player
    void setSpace(int, int, Square);

    //sets a position on the board to empty
    void setEmpty(int, int);

    Move_Vector get_moves() const;
    Color get_winner() const;

    void generate_possible_moves(int, int, Piece);

    void clear_moves();

private:
    Square squares_[8][8]; // 8 rows, 8 columns
    Color turn_   = Color::White;
    Color winner_ = Color::None;
    std::vector<Board::Position> straight_dir();
    std::vector<Board::Position> diagonal_dir();
    Move_Vector moves_;
  };
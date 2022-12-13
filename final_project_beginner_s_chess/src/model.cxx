#include "model.hxx"
#include "player.hxx"
#include "board.hxx"
#include <ge211.hxx>
#include <ostream>

Model::Model()
{
    //initializing the chess board at beginning of game
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            //pawns
            if (j == 1) {
                setPandC(i,j,Piece::Pawn, Color::Black);
            }
            if (j == 6) {
                setPandC(i,j,Piece::Pawn, Color::White);
            }
        }
    }

    //sets first row
    //sets rooks
    setPandC(0,0, Piece::Rook, Color::Black);
    setPandC(7,0,Piece::Rook, Color::Black);
    //sets knights
    setPandC(1,0,Piece::Knight, Color::Black);
    setPandC(6,0,Piece::Knight, Color::Black);
    //set bishops
    setPandC(2,0,Piece::Bishop, Color::Black);
    setPandC(5,0,Piece::Bishop, Color::Black);
    //set king
    setPandC(4,0,Piece::King, Color::Black);
    //set queen
    setPandC(3,0,Piece::Queen, Color::Black);

    //sets last row
    //sets rook
    setPandC(0,7,Piece::Rook, Color::White);
    setPandC(7,7,Piece::Rook, Color::White);
    //sets knights
    setPandC(1,7,Piece::Knight, Color::White);
    setPandC(6,7,Piece::Knight, Color::White);
    //set bishops
    setPandC(2,7,Piece::Bishop, Color::White);
    setPandC(5,7,Piece::Bishop, Color::White);
    //set king
    setPandC(4,7,Piece::King, Color::White);
    //set queen
    setPandC(3,7,Piece::Queen, Color::White);

}

//get a certain piece
Square
Model::square_at(int i, int j) const
{
    return squares_[i][j];
}

//changes turn
void
Model::switch_turn() {
    turn_ = other_player();
}

//gets current turn
Color
Model::get_turn() const
{
    return turn_;
}

//return other player
Color
Model::other_player() const
{
    if (turn_ == Color::White) {
        return Color::Black;
    }
    else {
        return Color::White;
    }
}

//returns winner
Color Model::get_winner() const {
    return winner_;
}

//Direction Functions
std::vector<Board::Position>
Model::straight_dir()
{
    std::vector<Board::Position> result;
    result.push_back(Board::Position {0, -1});
    result.push_back(Board::Position {1, 0});
    result.push_back(Board::Position {0, 1});
    result.push_back(Board::Position {-1, 0});
    return result;
}

std::vector<Board::Position>
Model::diagonal_dir()
{
    std::vector<Board::Position> result;

    result.push_back(Board::Position {-1, -1});
    result.push_back(Board::Position {1, -1});
    result.push_back(Board::Position {1, 1});
    result.push_back(Board::Position {-1, 1});
    return result;
}

//
// Square Class Functions
//

Square::Square() {
    piece_ = Piece::None;
    color_ = Color::None;
}

//returns piece name
Piece
Square::getPiece()
{
    return piece_;
}


//returns color of piece
Color
Square::getColor()
{
    return color_;
}

//sets a position on the board to a certain player
void
Square::setSpace(Square square)
{
    piece_ = square.piece_;
    color_ = square.color_;
}


//sets a position on the board to empty
void
Square::setEmpty()
{
    piece_ = Piece::None;
    color_ = Color::None;
}

//set piece and color

void
Square::setPandC(Piece piece, Color color)
{
    piece_ = piece;
    color_ = color;
}

//MODEL square functions

//sets a position on the board to a certain player
void
Model::setSpace(int i, int j, Square square)
{
    squares_[i][j].setSpace(square);
}


//sets a position on the board to empty
void
Model::setEmpty(int i, int j)
{
    squares_[i][j].setEmpty();
}

//set piece and color
void
Model::setPandC(int i, int j, Piece piece, Color color)
{
    squares_[i][j].setPandC(piece, color);
}


//
// Functions for moves vector
//

//returns the moves vector
Model::Move_Vector
Model::get_moves() const
{
    return moves_;
}

void
Model::clear_moves()
{
    moves_ = {};
}


void
Model::generate_possible_moves(int i1, int j1, Piece piece) {
    switch (piece) {
        case Piece::Pawn:
            pawn_moves(i1, j1);
            break;
        case Piece::Rook:
            rook_moves(i1, j1);
            break;
        case Piece::Bishop:
            bishop_moves(i1, j1);
            break;
        case Piece::Knight:
            knight_moves(i1, j1);
            break;
        case Piece::Queen:
            queen_moves(i1, j1);
            break;
        case Piece::King:
            king_moves(i1, j1);
            break;
        case Piece::None:
            break;
    }
}




//
// Good position functions
//

bool
Model::good_pos(int i, int j)
{
    //checks if the given ints are within the bounds of the board
    if ( i > 7 || j > 7 || i < 0 || j < 0) {
        return false;
    }
    else {
        return true;
    }
}

bool
Model::knight_good_pos (int i, int j)
{
    //checks if the given ints are within the bounds of the board
    if (good_pos(i, j)) {
        Color sq_color = square_at(i, j).getColor();

        //checks if a given square is empty, and if not, that the color of
        // the piece on that square is that of the opponent
        if (sq_color == Color::None || sq_color == other_player()) {
            return true;
        }
    }
    return false;
}

//executing moves
void
Model::execute_move(int i1, int j1, int i2, int j2)
{
    //initializes old_square as the square of the first click a player made
    // (ie the piece they wanted to move to a different spot)
    Square old_square =  square_at(i1, j1);
    //initializes the new_space as a position of the space the player wanted
    // to move a piece to
    std::vector<int> new_space{i2, j2};
    //initializes a variable called move which will later be filled with the
    // available spots for a given piece the player wishes to move

    //executes a move by first checking if the space the player wishes to
    // move to is in the vector of possible moves. if so, reassigns the piece
    // they wished to move to the spot they wished to move it to and clears
    // the spot the piece was original

    for (std::vector<int> move: moves_) {
        if (move == new_space) {
            //if new space is equal to king

            if (square_at(i2,j2).getPiece() == Piece::King) {
                if (square_at(i2,j2).getColor() == Color::White){
                    winner_ = Color::Black;
                }
                else if(square_at(i2,j2).getColor() == Color::Black) {
                    winner_ = Color::White;
                }
            }

            setSpace(i2, j2, old_square);
            setEmpty(i1,j1);
            switch_turn();
            std::cout<<"switched turn \n";

        }
    }

}


//helper function that gets all possible moves for a piece in a given direction
void
Model::find_moves(
        int i,
        int j,
        Board::Position dir)
{
    //add dir to i and j coordinates of vector
    int new_i = i + dir.x, new_j = j + dir.y;

    //while the position is good
    while (good_pos(new_i, new_j)) {
        Square curr = square_at(new_i, new_j);
        //if color is none means empty pathway
        if (curr.getColor() == Color::None) {
            moves_.push_back({new_i, new_j});
            new_i += dir.x, new_j += dir.y;
        }
        //if color is other player means we can take it
        else if (curr.getColor() == other_player()) {
            moves_.push_back({new_i, new_j});
            break;
        }
            //if color is curren turn means blocked
        else if (curr.getColor() == get_turn()) {
            break;
        }
    }
}


void
Model::rook_moves(int i, int j)
{
    //initialize vector containing the possible moves

    //iterate through all the straight directions (rook only move straight)
    for (Board::Position dir : straight_dir()) {
        find_moves(i, j, dir);
    }

    //returns vector with all possible moves in all directions
}

void
Model::bishop_moves(int i, int j)
{
    //initialize vector containing the possible moves

    //iterate through all the diagonal directions (bishop only move dia)
    for (Board::Position dir : diagonal_dir()) {
        find_moves( i, j, dir);
    }

    //returns vector with all possible moves in all directions

}

void
Model::queen_moves(int i, int j)
{
    //initialize vector containing the possible moves

    //iterate through all the diagonal directions
    for (Board::Position dir : diagonal_dir()) {
        find_moves(i, j, dir);
    }

    //iterate through all the straight directions
    for (Board::Position dir : straight_dir()) {
        find_moves(i, j, dir);
    }

    //returns vector with all possible moves in all directions
}

void
Model::knight_moves(int i, int j)
{

    for (Board::Position dir : diagonal_dir()) {
        int new_i = i + 2*dir.x, new_j = j + dir.y;

        if (knight_good_pos(new_i, new_j)) {
            moves_.push_back(std::vector<int> {new_i, new_j});
        }
    }

    for (Board::Position dir : diagonal_dir()) {
        int new_i = i + dir.x, new_j = j + 2*dir.y;

        if (knight_good_pos(new_i, new_j)) {
            moves_.push_back(std::vector<int> {new_i, new_j});
        }
    }

}

void
Model::king_moves(int i, int j)
{

    for (Board::Position dir : diagonal_dir()) {
        int new_i = i + dir.x, new_j = j + dir.y;
        Square curr = square_at(new_i, new_j);

        if (!good_pos(new_i, new_j)) {
            break;
        }

        if (curr.getColor() == Color::None) {
            moves_.push_back(std::vector<int> {new_i, new_j});
        }
        else if (curr.getColor() == other_player()) {
            moves_.push_back(std::vector<int> {new_i, new_j});
        }
    }

    for (Board::Position dir : straight_dir()) {
        int new_i = i + dir.x, new_j = j + dir.y;
        Square curr = square_at(new_i, new_j);

        if (curr.getColor() == Color::None) {
            moves_.push_back(std::vector<int> {new_i, new_j});
        }
        else if (curr.getColor() == other_player()) {
            moves_.push_back(std::vector<int> {new_i, new_j});
        }
    }
}

//pawn moves
void
Model::pawn_moves(int i, int j)
{

    //if pawn is in the second or 6th row, pawn can move 1 or 2 up
    if (get_turn() == Color::White) {
        if (j == 6) {
            //pawn can move up at least 2 pieces
            for (int k = 1; k < 3; k++) {
                if (good_pos(i, j - k)) {
                    Square curr = square_at(i, j - k);
                    if (curr.getColor() == Color::None) {
                        moves_.push_back(std::vector<int> {i, j - k});
                    }
                        //if you hit your piece or another piece, return
                    else {
                        break;
                    }
                }
            }
        }
        else if (good_pos(i, j - 1)) {
            Square curr = square_at(i, j - 1);
            if (curr.getColor() == Color::None) {
                moves_.push_back(std::vector<int> {i, j - 1});
            }
        }
        //checks if a pawn can capture an opponent diagonally
        if (good_pos(i + 1, j-1)) {
            Square curr = square_at(i+1, j-1);
            if (curr.getColor() == Color::Black) {
                moves_.push_back(std::vector<int> {i+1, j-1});
            }
        }
        if (good_pos(i - 1, j-1)) {
            Square curr = square_at(i-1, j-1);
            if (curr.getColor() == Color::Black) {
                moves_.push_back(std::vector<int> {i-1, j-1});
            }
        }
    }

    if (get_turn() == Color::Black) {
        if (j == 1) {
            //pawn can move up at least 2 pieces
            for (int k = 1; k < 3 ; k++) {
                if (good_pos(i , j+k)) {
                    Square curr = square_at(i, j+k);
                    if (curr.getColor() == Color::None) {
                        moves_.push_back(std::vector<int> {i, j+k});
                    }
                    else {
                        break;
                    }
                }
            }
        }
            //if not, then pawn can only move one up
        else if (good_pos(i , j+1)) {
            Square curr = square_at(i, j+1);
            if (curr.getColor() == Color::None) {
                moves_.push_back(std::vector<int> {i, j+1});
            }
        }
        //checks if pawn can capture opponent diagonally
        if (good_pos(i - 1, j+1)) {
            Square curr = square_at(i-1, j+1);
            if (curr.getColor() == Color::White) {
                moves_.push_back(std::vector<int> {i-1, j+1});
            }
        }
        if (good_pos(i + 1, j+1)) {
            Square curr = square_at(i+1, j+1);
            if (curr.getColor() == Color::White) {
                moves_.push_back(std::vector<int> {i+1, j+1});
            }
        }
    }
}

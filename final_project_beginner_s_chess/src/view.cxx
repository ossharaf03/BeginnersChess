#include "view.hxx"
#include "player.hxx"
#include "model.hxx"

// Convenient type aliases:
using Hue = ge211::Color;
using Sprite_set = ge211::Sprite_set;

// Initializing grid sizes
static int const square_size = 66;


// Initializing Colors
static Hue const green {50, 168, 70};
static Hue const white {255, 255, 255};
static Hue const red{255, 160, 222};
static Hue const pink{250, 202, 233};
static Hue const black{0,0,0};

View::View(Model const& model)
        : model_(model),
        // You may want to add sprite initialization here
          board_square_green_({square_size, square_size}, green),
          board_square_white_({square_size, square_size}, white),
          red_sprite_({square_size,square_size}, red),
          pink_sprite_({square_size,square_size}, pink),
          highlight_sprite_({425,100}, black),
          wPawn_("white_pawn.png"),
          wRook_("white_rook.png"),
          wBishop_("white_bishop.png"),
          wKnight_("white_knight.png"),
          wQueen_("white_queen.png"),
          wKing_("white_king.png"),
          bPawn_("black_pawn.png"),
          bRook_("black_rook.png"),
          bBishop_("black_bishop.png"),
          bKnight_("black_knight.png"),
          bQueen_("black_queen.png"),
          bKing_("black_king.png")
{ }

void View::draw(Sprite_set& set, Position pos, bool piece)
{
    //draw grid
    for (int i = 0; i < model_.grid_size; i++) {
        for (int j = 0; j < model_.grid_size; j++) {
            //set.add_sprite(light_player_sprite,
            //{i * cell_size, j *cell_size}
            //, 3);
            if ((i + j) % 2 == 0) {
                set.add_sprite(board_square_green_,
                               {i * cell_size, j * cell_size});
            }
            else {
                set.add_sprite(board_square_white_,
                               {i * cell_size, j * cell_size});
            }
            add_player_sprite_(set, model_.square_at(i,j), i, j);
        }
    }
    //add sprite for wherever player clicks
    Position p = screen_to_board(pos);
    if (piece) {
        set.add_sprite(red_sprite_, {p.x * cell_size, p.y * cell_size}, 1);
    }
    //find viable moves
    for (std::vector<int> move : model_.get_moves()) {
        set.add_sprite(pink_sprite_, {move[0] * cell_size, move[1] * cell_size}, 2);
    }
    //sprite for winner
    if (model_.get_winner() == Color::Black) {
        ge211::Text_sprite::Builder name_builder(sans30_);
        name_builder.color(white) << "Black team has won!";
        b_winner_.reconfigure(name_builder);
        set.add_sprite(highlight_sprite_, {90,250}, 6);
        set.add_sprite(b_winner_, {120, 260}, 8);
    }
    else if (model_.get_winner() == Color::White) {
        ge211::Text_sprite::Builder name_builder(sans30_);
        name_builder.color(white) << "White team has won!";
        w_winner_.reconfigure(name_builder);
        set.add_sprite(highlight_sprite_, {90,250}, 6);
        set.add_sprite(w_winner_, {120,260}, 8);
    }



}
View::Dimensions
View::initial_window_dimensions() const
{
    // You can change this if you want:
    return {cell_size * model_.grid_size, cell_size * model_.grid_size};
}

std::string
View::initial_window_title() const
{
    // You can change this if you want:
    return "Beginners Chess";
}
View::Position
View::screen_to_board(View::Position pos) const
{
    return {pos.x / cell_size, pos.y / cell_size};
}
void
View::add_player_sprite_(
        Sprite_set& set,
        Square square,
        int i,
        int j) const
{
    //white pawn
    if (square.getColor() == Color::White && square.getPiece() == Piece::
    Pawn) {
        set.add_sprite(wPawn_, {i * cell_size, j * cell_size}, 5);
    }
    //white rook
    if (square.getColor() == Color::White && square.getPiece() == Piece::
    Rook) {
        set.add_sprite(wRook_, {i * cell_size, j * cell_size}, 5);
    }
    //white bishop
    if (square.getColor() == Color::White && square.getPiece() == Piece::
    Bishop){
        set.add_sprite(wBishop_, {i * cell_size, j * cell_size}, 5);
    }
    //white knight
    if (square.getColor() == Color::White && square.getPiece() == Piece::
    Knight){
        set.add_sprite(wKnight_, {i * cell_size, j * cell_size}, 5);
    }
    //white queen
    if (square.getColor() == Color::White && square.getPiece() == Piece::
    Queen){
        set.add_sprite(wQueen_, {i * cell_size, j * cell_size}, 5);
    }
    //white king
    if (square.getColor() == Color::White && square.getPiece() == Piece::
    King){
        set.add_sprite(wKing_, {i * cell_size, j * cell_size}, 5);
    }
    //black pawn
    if (square.getColor() == Color::Black && square.getPiece() == Piece::
    Pawn) {
        set.add_sprite(bPawn_, {i * cell_size, j * cell_size}, 5);
    }
    //black rook
    if (square.getColor() == Color::Black && square.getPiece() == Piece::
    Rook) {
        set.add_sprite(bRook_, {i * cell_size, j * cell_size}, 5);
    }
    //black bishop
    if (square.getColor() == Color::Black && square.getPiece() == Piece::
    Bishop) {
        set.add_sprite(bBishop_, {i * cell_size, j * cell_size}, 5);
    }
    //black knight
    if (square.getColor() == Color::Black && square.getPiece() == Piece::
    Knight) {
        set.add_sprite(bKnight_, {i * cell_size, j * cell_size}, 5);
    }
    //black queen
    if (square.getColor() == Color::Black && square.getPiece() == Piece::
    Queen) {
        set.add_sprite(bQueen_, {i * cell_size, j * cell_size}, 5);
    }
    //black king
    if (square.getColor() == Color::Black && square.getPiece() == Piece::
    King) {
        set.add_sprite(bKing_, {i * cell_size, j * cell_size}, 5);
    }
}

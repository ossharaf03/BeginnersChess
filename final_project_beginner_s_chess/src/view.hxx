#pragma once

#include "model.hxx"
#include "player.hxx"
#include "model.hxx"
#include <string>
static const int cell_size = 75;

class View
{
public:
    /// View dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// View positions will use `int` coordinates.
    using Position = ge211::Posn<int>;

    /// View rectangles will use `int` coordinates.
    using Rectangle = ge211::Rect<int>;

    /// Constructs a view that knows about the given model.
    explicit View(Model const&);

    // TODO: your code here
    // You will probably want to add arguments here so that the
    // controller can communicate UI state (such as a mouse or
    // cursor position):
    void draw(ge211::Sprite_set& set, Position pos, bool piece);

    Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;


    // TODO: Add any public member functions you need.
    Position screen_to_board(Position screen_pos) const;


private:
    Model const& model_;

    // TODO: Add any additional private members you need, such as helper
    // functions or sprites.
    ge211::Rectangle_sprite const board_square_green_;
    ge211::Rectangle_sprite const board_square_white_;
    ge211::Rectangle_sprite const red_sprite_;
    ge211::Rectangle_sprite const pink_sprite_;
    ge211::Rectangle_sprite const highlight_sprite_;
    ge211:: Image_sprite const wPawn_;
    ge211:: Image_sprite const wRook_;
    ge211:: Image_sprite const wBishop_;
    ge211:: Image_sprite const wKnight_;
    ge211:: Image_sprite const wQueen_;
    ge211:: Image_sprite const wKing_;
    ge211:: Image_sprite const bPawn_;
    ge211:: Image_sprite const bRook_;
    ge211:: Image_sprite const bBishop_;
    ge211:: Image_sprite const bKnight_;
    ge211:: Image_sprite const bQueen_;
    ge211:: Image_sprite const bKing_;
    ge211::Font sans30_{"sans.ttf", 40};
    ge211::Text_sprite b_winner_;
    ge211::Text_sprite w_winner_;


    void add_player_sprite_(ge211::Sprite_set&, Square, int, int) const;
};

/*******************************************/
/*** DO NOT CHANGE ANYTHING IN THIS FILE ***/
/*******************************************/

#pragma once

//#include "player.hxx"
//#include "move.hxx"

#include <ge211.hxx>

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>


/// Represents the state of the board.
class Board
{
public:
    //
    // HELPFUL TYPE ALIASES
    //

    /// Board dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// Board positions will use `int` coordinates.
    using Position = ge211::Posn<int>;

    /// Board rectangles will use `int` coordinates.
    using Rectangle = ge211::Rect<int>;

    // Defined and documented below.
    class reference;

private:
    //
    // PRIVATE DATA MEMBERS
    //

    Dimensions dims_;
    //Position_set light_;
    //position_set dark_;
    // INVARIANT: (light_ & dark_).empty()

public:
    //
    // PUBLIC CONSTRUCTOR & FUNCTION MEMBERS
    //

    /// Constructs a board with the given dimensions.
    ///
    /// ## Errors
    ///
    ///  - Throws `ge211::Client_logic_error` if either dimension is less
    ///    than 2 or greater than 8.
    explicit Board(Dimensions dims);

    /// Returns the same `Dimensions` value passed to the
    /// constructor.
    Dimensions dimensions() const;

    bool good_position(Position) const;

    /// Note that `Rectangle`s are considered to be closed on the top
    /// and left, but open on the bottom and right. The iterator will visit
    /// the correct positions for the board.
    Rectangle all_positions() const;
};
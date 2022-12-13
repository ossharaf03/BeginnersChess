#include <catch.hxx>
#include "player.hxx"
#include "move.hxx"
#include "board.hxx"
#include <ge211.hxx>
#include "model.hxx"
#include <algorithm>

/*
5 SIGNIFICANT MODEL TESTS:

 1. Tests that a valid move is executed (piece is moved to the new spot and old spot is cleared) L285-L300
 2. Tests that after a valid move is executed the turn changes L305-L312
 3. Tests that if a player makes an illegal move, nothing happens and the turn stays the same L316-L347
 4. Checks that the winner is not set until after a team captures the opposing team's king L350-L368
 5. Checks that, for a given piece on that player's turn, the correct set of valid moves is generated L373-L495

 */

TEST_CASE("test model initialization")
{
    Model m = Model();

    CHECK(m.get_turn() == Color::White);
    CHECK(m.other_player() == Color::Black);
    CHECK(m.square_at(0,0).getPiece() == Piece::Rook);
    CHECK(m.square_at(0,0).getColor() == Color::Black);
    CHECK(m.square_at(1,0).getPiece() == Piece::Knight);
    CHECK(m.square_at(1,0).getColor() == Color::Black);
    CHECK(m.square_at(2,0).getPiece() == Piece::Bishop);
    CHECK(m.square_at(2,0).getColor() == Color::Black);
    CHECK(m.square_at(3,0).getPiece() == Piece::Queen);
    CHECK(m.square_at(3,0).getColor() == Color::Black);
    CHECK(m.square_at(4,0).getPiece() == Piece::King);
    CHECK(m.square_at(4,0).getColor() == Color::Black);
    CHECK(m.square_at(7,0).getPiece() == Piece::Rook);
    CHECK(m.square_at(7,0).getColor() == Color::Black);
    CHECK(m.square_at(6,0).getPiece() == Piece::Knight);
    CHECK(m.square_at(6,0).getColor() == Color::Black);
    CHECK(m.square_at(5,0).getPiece() == Piece::Bishop);
    CHECK(m.square_at(5,0).getColor() == Color::Black);

    CHECK(m.square_at(0,7).getPiece() == Piece::Rook);
    CHECK(m.square_at(0,7).getColor() == Color::White);
    CHECK(m.square_at(1,7).getPiece() == Piece::Knight);
    CHECK(m.square_at(1,7).getColor() == Color::White);
    CHECK(m.square_at(2,7).getPiece() == Piece::Bishop);
    CHECK(m.square_at(2,7).getColor() == Color::White);
    CHECK(m.square_at(3,7).getPiece() == Piece::Queen);
    CHECK(m.square_at(3,7).getColor() == Color::White);
    CHECK(m.square_at(4,7).getPiece() == Piece::King);
    CHECK(m.square_at(4,7).getColor() == Color::White);
    CHECK(m.square_at(7,7).getPiece() == Piece::Rook);
    CHECK(m.square_at(7,7).getColor() == Color::White);
    CHECK(m.square_at(6,7).getPiece() == Piece::Knight);
    CHECK(m.square_at(6,7).getColor() == Color::White);
    CHECK(m.square_at(5,7).getPiece() == Piece::Bishop);
    CHECK(m.square_at(5,7).getColor() == Color::White);

    CHECK(m.square_at(4,4).getPiece() == Piece::None);
    CHECK(m.square_at(4,4).getColor() == Color::None);
}


//
// TODO: Write preliminary model tests.
//
// These tests should demonstrate your functional requirements.
//

//
// PLAYER TESTS
//

TEST_CASE("test player functions")
{
    Model model_ = Model();

    CHECK(model_.square_at(1,1).getPiece() == Piece::Pawn);
    CHECK(model_.square_at(1,1).getColor() == Color::Black);

    model_.setEmpty(1,1);
    CHECK(model_.square_at(1,1).getPiece() == Piece::None);
    CHECK(model_.square_at(1,1).getColor() == Color::None);

    model_.setSpace(1, 1, model_.square_at(0,1));
    CHECK(model_.square_at(1,1).getPiece() == Piece::Pawn);
    CHECK(model_.square_at(1,1).getColor() == Color::Black);

    model_.setEmpty(1,1);
    model_.setPandC(1, 1, Piece::Pawn, Color::Black);
    CHECK(model_.square_at(1,1).getPiece() == Piece::Pawn);
    CHECK(model_.square_at(1,1).getColor() == Color::Black);

}


//
// MOVE TESTS
//

TEST_CASE("Test good positions")
{
    Model model_ = Model();

    CHECK(model_.get_turn() == Color::White);
    CHECK(model_.other_player() == Color::Black);

    CHECK (model_.good_pos(1,1) == true);
    CHECK (model_.good_pos(9,9) == false);
    CHECK (model_.knight_good_pos(1,1) == true);
    CHECK (model_.knight_good_pos(7,7) == false);
    CHECK (model_.knight_good_pos(4,4) == true);
}

TEST_CASE("Test find_moves ends with opposing player")
{
    Model model_ = Model();

    model_.setPandC(4,3,Piece::Pawn, Color::Black);

    model_.find_moves(0, 3, {1,0});
    CHECK(model_.get_moves() == Model::Move_Vector {{1,3}, {2,3}, {3,3}, {4,3}});
}

TEST_CASE("Test find_moves ends with friendly player")
{
    Model model_ = Model();
    model_.setPandC(4,3,Piece::Pawn, Color::White);

    model_.find_moves( 0, 3, {1,0});

    CHECK(model_.get_moves() == Model::Move_Vector {{1,3}, {2,3}, {3,3}});

    model_.clear_moves();

    CHECK(model_.get_moves() == Model::Move_Vector {});

}

TEST_CASE("Test find_moves ends by hitting border")
{
    Model model_ = Model();

    model_.find_moves( 0, 3, {1,0});

    CHECK(model_.get_moves() == Model::Move_Vector {{1,3}, {2,3}, {3,3}, {4,3}, {5,3}, {6,3}, {7,3}});
}


TEST_CASE("Test find_moves over multiple directions")
{
    Model model_ = Model();

    model_.find_moves( 1, 3, {1,0});
    CHECK(model_.get_moves() == Model::Move_Vector {{2,3}, {3,3}, {4,3}, {5,3}, {6,3}, {7,3}});

    model_.find_moves( 1, 3, {-1,0});
    CHECK(model_.get_moves() == Model::Move_Vector {{2,3}, {3,3}, {4,3}, {5,3}, {6,3}, {7,3}, {0,3}});
}

TEST_CASE("Test Rook Moves")
{
    Model model_ = Model();

    model_.rook_moves(0,7);
    CHECK(model_.get_moves() == Model::Move_Vector {});

    Model::Move_Vector test =
            {
            {3,2}, {3,1},
            {4,3}, {5,3}, {6,3}, {7,3},
            {3,4}, {3,5},
            {2,3}, {1,3}, {0,3} };

    model_.rook_moves(3,3);
    CHECK(model_.get_moves() == test);
}

TEST_CASE("Test Bishop Moves")
{
    Model model_ = Model();

    Model::Move_Vector test =
            {
                    {2,2}, {1,1},
                    {4,2}, {5,1},
                    {4,4}, {5,5},
                    {2,4}, {1,5}};

    model_.bishop_moves(3,3);
    CHECK(model_.get_moves() == test);
}

TEST_CASE("Test Queen Moves")
{
    Model model_ = Model();

    Model::Move_Vector test =
            {
                    {2,2}, {1,1},
                    {4,2}, {5,1},
                    {4,4}, {5,5},
                    {2,4}, {1,5},
                    {3,2}, {3,1},
                    {4,3}, {5,3}, {6,3}, {7,3},
                    {3,4}, {3,5},
                    {2,3}, {1,3}, {0,3}};

    model_.queen_moves(3,3);
    CHECK(model_.get_moves() == test);
}

TEST_CASE("test knight moves") {
    Model model_ = Model();
    model_.knight_moves(6,7);
    Model::Move_Vector test = {{5,5}, {7,5}};
    CHECK(model_.get_moves() == test);
    //check knight for any position on the board
    model_.switch_turn();
    CHECK(model_.get_turn() == Color::Black);
    model_.clear_moves();
    model_.knight_moves(3,4);
    test = {{1,3}, {5,3}, {5,5}, {1,5}, {2,2}, {4,2}, {4,6}, {2,6}};
    CHECK(model_.get_moves() == test);

}

TEST_CASE("test king moves") {
    Model model_ = Model();

    Model::Move_Vector test =
            {
                    {2,2}, {4,2}, {4,4}, {2,4},
                    {3,2}, {4,3}, {3,4}, {2,3}};

    model_.king_moves(3,3);
    CHECK(model_.get_moves() == test);
}

TEST_CASE("Test Pawn Moves")
 {
    Model model_ = Model();

    //white pawn on white turn
    Model::Move_Vector test1 =
             { {1,5}, {1,4} };

    model_.pawn_moves(1,6);
    CHECK(model_.get_moves() == test1);
    model_.clear_moves();

    model_.setPandC(0,5, Piece::Pawn, Color::Black);
    model_.setPandC(2,5, Piece::Pawn, Color::Black);
    Model::Move_Vector test2 =
             { {1,5}, {1,4}, {2,5}, {0,5}};
    model_.pawn_moves(1,6);
    CHECK(model_.get_moves() == test2);
    model_.clear_moves();

    model_.pawn_moves(1,5);
    CHECK(model_.get_moves() == Model::Move_Vector {{1,4}});
    model_.clear_moves();

     //black pawn on black turn
     model_.switch_turn();

     Model::Move_Vector test3 =
             { {1,2}, {1,3} };

     model_.pawn_moves(1,1);
     CHECK(model_.get_moves() == test3);
     model_.clear_moves();

     model_.setPandC(0,2, Piece::Pawn, Color::White);
     model_.setPandC(2,2, Piece::Pawn, Color::White);
     Model::Move_Vector test4 =
             { {1,2}, {1,3}, {0,2}, {2,2}};
     model_.pawn_moves(1,1);
     CHECK(model_.get_moves() == test4);
     model_.clear_moves();

     model_.pawn_moves(1,2);
     CHECK(model_.get_moves() == Model::Move_Vector {{1,3}});
 }

 //
 // TESTING EXECUTE_MOVE
 //

TEST_CASE("test execute move") {
    Model model_ = Model();

    CHECK(model_.square_at(6,7).getPiece() == Piece::Knight);
    CHECK(model_.square_at(6,7).getColor() == Color::White);

    CHECK(model_.square_at(7,5).getPiece() == Piece::None);
    CHECK(model_.square_at(7,5).getColor() == Color::None);
    model_.generate_possible_moves(6,7, Piece::Knight);
    //this is a viable move for the knight, so the positions on the board should change (move
    //should be executed)
    model_.execute_move(6,7,7,5);

    CHECK(model_.square_at(6,7).getPiece() == Piece::None);
    CHECK(model_.square_at(6,7).getColor() == Color::None);

    CHECK(model_.square_at(7,5).getPiece() == Piece::Knight);
    CHECK(model_.square_at(7,5).getColor() == Color::White);
}

TEST_CASE("check turn is initialized to white and advances to black after executing valid move") {
    Model model_ = Model();
    CHECK(model_.get_turn() == Color::White);
    //execute a viable knight move and check that the turn changes
    model_.generate_possible_moves(6,7, Piece::Knight);
    model_.execute_move(6,7,7,5);
    CHECK(model_.get_turn() == Color::Black);
}

TEST_CASE("check that if a player makes illegal move, nothing happens and still their turn") {
    Model model_ = Model();

    CHECK(model_.square_at(6,7).getPiece() == Piece::Knight);
    CHECK(model_.square_at(6,7).getColor() == Color::White);

    CHECK(model_.square_at(0,0).getPiece() == Piece::Rook);
    CHECK(model_.square_at(0,0).getColor() == Color::Black);

    CHECK(model_.get_turn() == Color::White);

    model_.generate_possible_moves(6,7, Piece::Knight);
    std::vector<int> new_move{0,0};
    bool check = false;

    for (std::vector<int> move: model_.get_moves()) {
        if (move == new_move) {
            check = true;
        }
    }

    CHECK(check == false);
    model_.execute_move(6,7,0,0);

    CHECK(model_.get_turn() == Color::White);

    CHECK(model_.square_at(6,7).getPiece() == Piece::Knight);
    CHECK(model_.square_at(6,7).getColor() == Color::White);

    CHECK(model_.square_at(0,0).getPiece() == Piece::Rook);
    CHECK(model_.square_at(0,0).getColor() == Color::Black);
}

TEST_CASE("check that winner is only set after king is captured") {
    Model model_ = Model();
    CHECK(model_.get_winner() == Color::None);
    model_.setPandC(3,1, Piece::Pawn, Color::White);
    model_.generate_possible_moves(3,1, Piece::Pawn);
    std::vector<int> new_move{4,0};
    bool check = false;

    for (std::vector<int> move: model_.get_moves()) {
        if (move == new_move) {
            check = true;
        }
    }

    CHECK(check == true);
    //4,0 is where the black king is, so this would capture king
    model_.execute_move(3,1,4,0);
    CHECK(model_.get_winner() == Color::White);
}

//
TEST_CASE("check that generate_possible_moves gets the proper viable moves for a given player") {
    Model model_ = Model();

    //test rook moves
    model_.generate_possible_moves(0,7, Piece::Rook);
    //no viable moves so move vector is empty
    CHECK(model_.get_moves() == Model::Move_Vector {});

    Model::Move_Vector test_rook =
            {
            {3,2}, {3,1},
            {4,3}, {5,3}, {6,3}, {7,3},
            {3,4}, {3,5},
            {2,3}, {1,3}, {0,3} };

    //check generate moves comes up w all viable positions rook can take
    model_.setPandC(3,3,Piece::Rook, Color::White);
    model_.generate_possible_moves(3,3, Piece::Rook);
    CHECK(model_.get_moves() == test_rook);
    model_.clear_moves();
    model_.setEmpty(3,3);

    //test bishop moves
    Model::Move_Vector test_bishop =
            {
            {2,2}, {1,1},
            {4,2}, {5,1},
            {4,4}, {5,5},
            {2,4}, {1,5}};

    model_.setPandC(3,3,Piece::Bishop, Color::White);
    model_.generate_possible_moves(3,3, Piece::Bishop);
    CHECK(model_.get_moves() == test_bishop);
    model_.clear_moves();
    model_.setEmpty(3,3);

    //test queen moves
    Model::Move_Vector test_queen =
            {
            {2,2}, {1,1},
            {4,2}, {5,1},
            {4,4}, {5,5},
            {2,4}, {1,5},
            {3,2}, {3,1},
            {4,3}, {5,3}, {6,3}, {7,3},
            {3,4}, {3,5},
            {2,3}, {1,3}, {0,3}};
    model_.setPandC(3,3, Piece::Queen, Color::White);
    model_.generate_possible_moves(3,3, Piece::Queen);
    CHECK(model_.get_moves() == test_queen);
    model_.clear_moves();
    model_.setEmpty(3,3);

    //test knight moves
    model_.generate_possible_moves(6,7, Piece::Knight);
    Model::Move_Vector test_knight = {{5,5}, {7,5}};
    CHECK(model_.get_moves() == test_knight);
    //check knight for any position on the board
    model_.switch_turn();
    CHECK(model_.get_turn() == Color::Black);
    model_.clear_moves();
    model_.setPandC(3,4, Piece::Knight, Color::Black);
    model_.generate_possible_moves(3,4, Piece::Knight);
    Model::Move_Vector test_knight_2 = {{1,3}, {5,3}, {5,5}, {1,5}, {2,2}, {4,2}, {4,6}, {2,6}};
    CHECK(model_.get_moves() == test_knight_2);
    model_.clear_moves();
    model_.setEmpty(3,4);
    model_.switch_turn();

    //test king
    Model::Move_Vector test_king =
            {
            {2,2}, {4,2}, {4,4}, {2,4},
            {3,2}, {4,3}, {3,4}, {2,3}};

    model_.setPandC(3,3,Piece::King, Color::White);
    model_.generate_possible_moves(3,3, Piece::King);
    CHECK(model_.get_moves() == test_king);
    model_.clear_moves();
    model_.setEmpty(3,3);


   //test pawn moves
   //white pawn on white turn
   Model::Move_Vector test1 =
           { {1,5}, {1,4} };
   model_.generate_possible_moves(1,6, Piece::Pawn);
   CHECK(model_.get_moves() == test1);
   model_.clear_moves();

   model_.setPandC(0,5, Piece::Pawn, Color::Black);
   model_.setPandC(2,5, Piece::Pawn, Color::Black);
   Model::Move_Vector test2 =
           { {1,5}, {1,4}, {2,5}, {0,5}};
   model_.generate_possible_moves(1,6, Piece::Pawn);
   CHECK(model_.get_moves() == test2);
   model_.clear_moves();

   model_.generate_possible_moves(1,5,Piece::Pawn);
   CHECK(model_.get_moves() == Model::Move_Vector {{1,4}});
   model_.clear_moves();

   //black pawn on black turn
   model_.switch_turn();

   Model::Move_Vector test3 =
           { {1,2}, {1,3} };

   model_.generate_possible_moves(1,1, Piece::Pawn);
   CHECK(model_.get_moves() == test3);
   model_.clear_moves();

   model_.setPandC(0,2, Piece::Pawn, Color::White);
   model_.setPandC(2,2, Piece::Pawn, Color::White);
   Model::Move_Vector test4 =
           { {1,2}, {1,3}, {0,2}, {2,2}};
   model_.generate_possible_moves(1,1,Piece::Pawn);
   CHECK(model_.get_moves() == test4);
   model_.clear_moves();

   model_.generate_possible_moves(1,2, Piece::Pawn);
   CHECK(model_.get_moves() == Model::Move_Vector {{1,3}});
}


#include "controller.hxx"
#include "player.hxx"
#include "board.hxx"
#include "model.hxx"

Controller::Controller()
        : view_(model_),
          mouse_pos_(0,0)
{ }

//user quits by pressing q
void
Controller::on_key(ge211::Key key) {
   if (key == ge211::Key::code('q')) {
        quit();
    }
}

bool piece_selected = false;
Board::Position piece = {0,0};

void
Controller::on_mouse_up(ge211::Mouse_button, ge211::Posn<int> pos)
{
    mouse_pos_ = pos;
    std::cout << "mouse click" << mouse_pos_;
    Board::Position new_pos = view_.screen_to_board(pos);

    //if not in check and no piece is already selected and the player clicks on one of their
    // pieces, the coordinates of that piece are saved
    if (model_.get_winner() == Color::None) {
        if (!piece_selected) {
            std::cout << "Went in \n";
            if (model_.square_at(new_pos.x, new_pos.y).getColor() ==
                model_.get_turn()) {
                piece = {new_pos};
                piece_selected = true;
                model_.clear_moves();
                model_.generate_possible_moves(new_pos.x, new_pos.y, model_.square_at(new_pos.x, new_pos.y).getPiece());
            }
        }
            //if want to select another piece of your own
        else if (piece_selected) {
            std::cout << "Went in to piece selected \n";
            if (model_.square_at(new_pos.x, new_pos.y).getColor() ==
                model_.get_turn()) {
                piece = {new_pos};
                model_.clear_moves();
                model_.generate_possible_moves(new_pos.x, new_pos.y, model_.square_at(new_pos.x, new_pos.y).getPiece());
            }
                //if you click an opposing piece
            else {
                std::cout << "moving to" << Board::Position{new_pos} << "\n";
                std::cout << piece.x << "\n";
                std::cout << piece.y << "\n";
                //model_.generate_possible_moves(piece.x, piece.y, model_.square_at(piece.x, piece.y).getPiece());
                model_.execute_move(piece.x, piece.y, new_pos.x, new_pos.y);
                model_.clear_moves();
                std::cout << "executed move";
                piece_selected = false;
            }
        }
    }
}



void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set, mouse_pos_, piece_selected);
}

View::Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string
Controller::initial_window_title() const
{
    return view_.initial_window_title();
}
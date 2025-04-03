#include "headers/Pieces/King.hpp"
#include "headers/Pieces/Piece.hpp"

King::King(Color color, const unsigned int position)
    : Piece(color, position), is_check{false}
{
    symbol         = "l";
    infinite_range = false;
};

void King::seach_positions_can_move(const std::vector<Piece*>& spaces, std::map<size_t, bool>& possible_moves, const unsigned int dim, const std::pair<Piece*, std::pair<size_t, size_t>> last_move)
{
    search_position_diagonal(spaces, possible_moves, dim);
    search_position_front_back_sides(spaces, possible_moves, dim);
}
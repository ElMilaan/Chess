#include "headers/Pieces/Queen.hpp"
#include "headers/Pieces/Piece.hpp"

Queen::Queen(Color color, const unsigned int position)
    : Piece(color, position)
{
    symbol         = "w";
    infinite_range = true;
};

void Queen::seach_positions_can_move(const std::vector<Piece*>& spaces, std::map<size_t, bool>& possible_moves, const unsigned int dim, const std::pair<Piece*, std::pair<size_t, size_t>> last_move)
{
    search_position_diagonal(spaces, possible_moves, dim);
    search_position_front_back_sides(spaces, possible_moves, dim);
}
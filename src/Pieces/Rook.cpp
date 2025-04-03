#include "headers/Pieces/Rook.hpp"
#include "headers/Pieces/Piece.hpp"

Rook::Rook(Color color, const unsigned int position)
    : Piece(color, position)
{
    symbol         = "t";
    infinite_range = true;
};

void Rook::seach_positions_can_move(const std::vector<Piece*>& spaces, std::map<size_t, bool>& possible_moves, const unsigned int dim, const std::pair<Piece*, std::pair<size_t, size_t>> last_move)
{
    search_position_front_back_sides(spaces, possible_moves, dim);
}
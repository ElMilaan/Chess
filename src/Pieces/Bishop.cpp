#include "headers/Pieces/Bishop.hpp"
#include "headers/Pieces/Piece.hpp"

Bishop::Bishop(Color color, const unsigned int position)
    : Piece(color, position)
{
    symbol         = "v";
    infinite_range = true;
};

void Bishop::seach_positions_can_move(const std::vector<Piece*>& spaces, std::map<size_t, bool>& possible_moves, const unsigned int dim, const std::pair<Piece*, std::pair<size_t, size_t>> last_move)
{
    search_position_diagonal(spaces, possible_moves, dim);
}
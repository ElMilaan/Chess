#pragma once
#include "Piece.hpp"

class Rook : public Piece {
public:
    Rook(Color color, const unsigned int position);
    void seach_positions_can_move(const std::vector<Piece*>& spaces, std::map<size_t, bool>& possible_moves, const unsigned int dim, const std::pair<Piece*, std::pair<size_t, size_t>> last_move) override;

private:
};
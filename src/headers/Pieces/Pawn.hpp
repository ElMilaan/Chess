#pragma once
#include "../history.hpp"
#include "Piece.hpp"

class Pawn : public Piece {
public:
    Pawn(Color color, const size_t position);
    void seach_positions_can_move(const std::vector<Piece*>& spaces, std::map<size_t, bool>& possible_moves, const unsigned int dim, const std::pair<Piece*, std::pair<size_t, size_t>> last_move) override;
    void first_move(const std::vector<Piece*>& spaces, std::map<size_t, bool>& possible_moves, const unsigned int dim);
    void can_eat(const std::vector<Piece*>& spaces, std::map<size_t, bool>& possible_moves, const unsigned int dim);
    void prise_en_passant(const std::vector<Piece*>& spaces, std::map<size_t, bool>& possible_moves, const unsigned int dim, const std::pair<Piece*, std::pair<size_t, size_t>> last_move);
    // void become_queen(std::vector<Piece*>& spaces, const unsigned int dim);

private:
};
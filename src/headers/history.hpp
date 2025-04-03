#pragma once

#include <iostream>
#include "Pieces/Bishop.hpp"
#include "Pieces/King.hpp"
#include "Pieces/Knight.hpp"
#include "Pieces/Pawn.hpp"
#include "Pieces/Queen.hpp"
#include "Pieces/Rook.hpp"

struct Move {
    size_t id;
    Piece* piece;
    size_t from_index;
    size_t to_index;
};

struct History {
    std::vector<Move>   moves;
    std::vector<Piece*> eaten_pieces;

    void add_move(Move move)
    {
        moves.push_back(move);
    }
    size_t nb_moves()
    {
        return moves.size();
    }
    void add_eaten_piece(Piece* piece)
    {
        eaten_pieces.push_back(std::move(piece));
    }
};
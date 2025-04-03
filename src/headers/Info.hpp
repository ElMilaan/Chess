#pragma once

#include <iostream>
#include "Board.hpp"
#include "Pieces/Bishop.hpp"
#include "Pieces/King.hpp"
#include "Pieces/Knight.hpp"
#include "Pieces/Pawn.hpp"
#include "Pieces/Queen.hpp"
#include "Pieces/Rook.hpp"
#include "history.hpp"

struct Info {
    Info()
        : current_turn_number(0), current_turn_color(WHITE), selected_piece(nullptr), nb_b_piece(16), nb_w_piece(16) {}

    size_t       current_turn_number;
    Color        current_turn_color;
    Piece*       selected_piece;
    unsigned int nb_w_piece;
    unsigned int nb_b_piece;
    History      history;

    void update(const Board& board, History& history);
    void render(const bool end_game = false, const Color winner = WHITE);
};
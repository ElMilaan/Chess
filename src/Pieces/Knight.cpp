#include "headers/Pieces/Knight.hpp"
#include "headers/Pieces/Piece.hpp"

Knight::Knight(Color color, const unsigned int position)
    : Piece(color, position)
{
    symbol         = "m";
    infinite_range = false;
};

void Knight::seach_positions_can_move(const std::vector<Piece*>& spaces, std::map<size_t, bool>& possible_moves, const unsigned int dim, const std::pair<Piece*, std::pair<size_t, size_t>> last_move)
{
    constexpr int directions[8][2] = {{-2, -1}, {-2, 1}, {2, -1}, {2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}};

    for (auto [row_step, col_step] : directions)
    {
        size_t row     = position / dim,
               col     = position % dim;
        size_t new_row = row + row_step,
               new_col = col + col_step;

        if (new_row < 0 || new_row >= dim || new_col < 0 || new_col >= dim)
            continue;

        size_t i = new_row * dim + new_col;
        Piece* p = spaces[i];

        if (p)
        {
            if (p->get_color() != color)
                possible_moves.insert({i, true});
        }
        else
        {
            possible_moves.insert({i, false});
        }
    }
}
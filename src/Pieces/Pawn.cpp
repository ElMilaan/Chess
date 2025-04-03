#include "headers/Pieces/Pawn.hpp"
#include "headers/Pieces/Piece.hpp"

Pawn::Pawn(Color color, const size_t position)
    : Piece(color, position)
{
    symbol         = "o";
    infinite_range = false;
};

void Pawn::seach_positions_can_move(const std::vector<Piece*>& spaces, std::map<size_t, bool>& possible_moves, const unsigned int dim, const std::pair<Piece*, std::pair<size_t, size_t>> last_move)
{
    if (!has_moved)
    {
        first_move(spaces, possible_moves, dim);
    }
    else
    {
        size_t pos = (color == WHITE) ? position - dim : position + dim;
        Piece* p   = spaces[pos];
        if (!p)
        {
            possible_moves.insert({pos, false});
        }
    }
    can_eat(spaces, possible_moves, dim);
    if (last_move.first)
        prise_en_passant(spaces, possible_moves, dim, last_move);
}

void Pawn::first_move(const std::vector<Piece*>& spaces, std::map<size_t, bool>& possible_moves, const unsigned int dim)
{
    for (size_t i{1}; i <= 2; i++)
    {
        size_t pos = (color == WHITE) ? position - i * dim : position + i * dim;
        Piece* p   = spaces[pos];
        if (p)
        {
            break;
        }
        else
        {
            possible_moves.insert({pos, false});
        }
    }
}

void Pawn::can_eat(const std::vector<Piece*>& spaces, std::map<size_t, bool>& possible_moves, const unsigned int dim)
{
    size_t pos1{(color == WHITE) ? position - (dim - 1) : position + (dim - 1)};
    size_t pos2{(color == WHITE) ? position - (dim + 1) : position + (dim + 1)};
    if (spaces[pos1] && spaces[pos1]->get_color() != color)
    {
        possible_moves.insert({pos1, true});
    }
    if (spaces[pos2] && spaces[pos2]->get_color() != color)
    {
        possible_moves.insert({pos2, true});
    }
}

void Pawn::prise_en_passant(const std::vector<Piece*>& spaces, std::map<size_t, bool>& possible_moves, const unsigned int dim, const std::pair<Piece*, std::pair<size_t, size_t>> last_move)
{
    size_t pos_white{last_move.second.first + dim};
    size_t pos_black{last_move.second.first - dim};
    if (strcmp(last_move.first->get_symbol(), "o") == 0)
    {
        if (color == WHITE && last_move.second.second == pos_white + dim && (pos_white + dim + 1 == position || pos_white + dim - 1 == position))
            possible_moves.insert({pos_white, true});

        else if (color == BLACK && last_move.second.second == pos_black - dim && (pos_black - dim - 1 == position || pos_black - dim + 1 == position))
            possible_moves.insert({pos_black, true});
    }
}

// void Pawn::become_queen(std::vector<Piece*>& spaces, const unsigned int dim)
// {
//     if (position < dim || position >= pow(dim, 2) - dim)
//     {
//         spaces[position] = new Queen(color, position);
//         delete this;
//     }
// }
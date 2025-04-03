#include "../headers/Pieces/Piece.hpp"
#include <math.h>
#include <algorithm>

Piece::Piece(Color color, const size_t position)
    : color(color), position(position), has_moved(false) {}

// GETTERS

Color Piece::get_color() const
{
    return color;
}

const char* Piece::get_symbol() const
{
    return symbol;
}

size_t Piece::get_position() const
{
    return position;
}

// SETTERS

void Piece::set_color(Color color) const
{
    color = color;
}

void Piece::set_position(const size_t new_position)
{
    position = new_position;
}

// METHODS

bool Piece::is_infinite_range() const
{
    return infinite_range;
}

void Piece::search_position_diagonal(const std::vector<Piece*>& spaces, std::map<size_t, bool>& possible_moves, const unsigned int dim)
{
    constexpr int directions[4][2] = {{-1, 1}, {-1, -1}, {1, 1}, {1, -1}};

    for (auto [row_step, col_step] : directions)
    {
        for (size_t i = position;;)
        {
            size_t row     = i / dim,
                   col     = i % dim;
            size_t new_row = row + row_step,
                   new_col = col + col_step;

            if (new_row < 0 || new_row >= dim || new_col < 0 || new_col >= dim)
                break;

            i        = new_row * dim + new_col;
            Piece* p = spaces[i];
            if (p)
            {
                if (p->get_color() != color)
                    possible_moves.insert({i, true});
                break;
            }
            else
            {
                possible_moves.insert({i, false});
            }

            if (!infinite_range)
                break;
        }
    }
}

void Piece::search_position_front_back_sides(const std::vector<Piece*>& spaces, std::map<size_t, bool>& possible_moves, const unsigned int dim)
{
    constexpr int directions[2] = {-1, 1};

    for (auto step : directions)
    {
        for (size_t i = position;;)
        {
            size_t row = i / dim;
            row += step;

            if (row < 0 || row >= dim)
                break;

            i        = row * dim + (position % dim);
            Piece* p = spaces[i];

            if (p)
            {
                if (p->get_color() != color)
                    possible_moves.insert({i, true});
                break;
            }
            else
            {
                possible_moves.insert({i, false});
            }

            if (!infinite_range)
                break;
        }

        for (size_t i = position;;)
        {
            size_t col = i % dim;
            col += step;

            if (col < 0 || col >= dim)
                break;

            i        = (position / dim) * dim + col;
            Piece* p = spaces[i];

            if (p)
            {
                if (p->get_color() != color)
                    possible_moves.insert({i, true});
                break;
            }
            else
            {
                possible_moves.insert({i, false});
            }

            if (!infinite_range)
                break;
        }
    }
}

void Piece::move(std::vector<Piece*>& spaces, size_t index)
{
    size_t current_position  = position;
    position                 = index;
    spaces[current_position] = nullptr;
    spaces[index]            = std::move(this);
    if (!has_moved)
        has_moved = true;
}

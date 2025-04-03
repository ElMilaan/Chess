#pragma once

#include <iostream>
#include <map>
#include "../utils.hpp"

class Piece {
public:
    Piece(Color color, const size_t position);
    virtual ~Piece() = default;

    void set_color(Color color) const;
    void set_position(const size_t new_position);

    Color       get_color() const;
    const char* get_symbol() const;
    size_t      get_position() const;
    bool        is_infinite_range() const;

    void search_position_diagonal(const std::vector<Piece*>& spaces, std::map<size_t, bool>& possible_moves, const unsigned int dim);
    void search_position_front_back_sides(const std::vector<Piece*>& spaces, std::map<size_t, bool>& possible_moves, const unsigned int dim);

    void         move(std::vector<Piece*>& spaces, size_t index);
    virtual void seach_positions_can_move(const std::vector<Piece*>& spaces, std::map<size_t, bool>& possible_moves, const unsigned int dim, const std::pair<Piece*, std::pair<size_t, size_t>> last_move) = 0;

protected:
    size_t      position;
    Color       color;
    const char* symbol;
    bool        infinite_range;
    bool        has_moved;
};
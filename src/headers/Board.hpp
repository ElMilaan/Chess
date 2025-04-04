#pragma once

#include <iostream>
#include <map>
#include <quick_imgui/quick_imgui.hpp>
#include <vector>
#include "Pieces/Bishop.hpp"
#include "Pieces/King.hpp"
#include "Pieces/Knight.hpp"
#include "Pieces/Pawn.hpp"
#include "Pieces/Queen.hpp"
#include "Pieces/Rook.hpp"
#include "history.hpp"

enum PieceType
{
    KING,
    QUEEN,
    BISHOP,
    KNIGHT,
    ROOK,
    PAWN
};

class Board
{
private:
    unsigned int dimension;
    unsigned int nb_w_pieces;
    unsigned int nb_b_pieces;
    std::vector<Piece *> spaces;
    Piece *selected_piece;
    std::map<size_t, bool> possible_spaces;
    Color turn;

public:
    static const unsigned int SPACE_SIZE{50};
    static const inline std::vector<PieceType> PIECES_DISPOSITION{ROOK, KNIGHT, BISHOP, KING, QUEEN, BISHOP, KNIGHT, ROOK};
    const ColorUI colors{};

    Board(unsigned int dimension);
    unsigned int get_dimension() const;
    Color get_turn() const;
    Piece *get_selected_piece() const;
    unsigned int get_nb_w_pieces() const;
    unsigned int get_nb_b_pieces() const;
    void set_dimension(unsigned int dimension) const;
    void handle_turn();

    void insert_piece(PieceType type, Color color, const size_t position);
    void fill_pieces();

    void init();
    void update(History &history);

    void set_space_style(Color color, const size_t index, int &nb_styles_push);
    void set_piece_style(const Piece *piece_ptr, const char *&space_label);

    void set_color_scope(ImU32 &color_scope, const bool is_enemy);
    void set_border_thickness(ImVec2 &button_min, ImVec2 &button_max, float border_thickness);
    void set_scope(const size_t index);

    void set_style(const size_t &index, Color color, int &nb_style_push, const Piece *p, const char *&space_label);
    void end_game(const Color loser);

    void no_action_button(const char *space_label);

    void first_click_button(size_t index, const char *space_label, History &history);

    void classic_eat(size_t index, History &history);
    void prise_en_passant(size_t index);
    void eat_piece(size_t index, History &history);
    void pawn_to_queen(Piece *&selected_piece, const size_t index);
    void move_piece(size_t index);
    void second_click_button(size_t index, const char *space_label, History &history);

    void create_button(size_t index, const char *space_label, History &history);
    void render(History &history);
};
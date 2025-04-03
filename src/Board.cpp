#include "headers/Board.hpp"
#include <math.h>

Board::Board(unsigned int dimension)
    : dimension(dimension), spaces(std::vector<Piece*>(pow(dimension, 2), nullptr)), nb_w_pieces(0), nb_b_pieces(0), turn(WHITE) {}

// SETTERS

void Board::set_dimension(unsigned int dimension) const
{
    dimension = dimension;
}

void Board::handle_turn()
{
    (turn == WHITE)
        ? turn = BLACK
        : turn = WHITE;
}

// GETTERS

unsigned int Board::get_dimension() const
{
    return dimension;
}

Color Board::get_turn() const
{
    return turn;
}

Piece* Board::get_selected_piece() const
{
    return selected_piece;
}

unsigned int Board::get_nb_w_pieces() const
{
    return nb_w_pieces;
}
unsigned int Board::get_nb_b_pieces() const
{
    return nb_b_pieces;
}

// METHODS

void Board::insert_piece(PieceType type, Color color, const size_t position)
{
    switch (type)
    {
    case PieceType::KING:
        spaces[position] = new King(color, position);
        break;
    case PieceType::QUEEN:
        spaces[position] = new Queen(color, position);
        break;
    case PieceType::BISHOP:
        spaces[position] = new Bishop(color, position);
        break;
    case PieceType::ROOK:
        spaces[position] = new Rook(color, position);
        break;
    case PieceType::KNIGHT:
        spaces[position] = new Knight(color, position);
        break;
    case PieceType::PAWN:
        spaces[position] = new Pawn(color, position);
        break;
    }
}

void Board::fill_pieces()
{
    size_t piece_index_start{0}, piece_index_end{(size_t)pow(dimension, 2) - 1};
    for (PieceType pt : PIECES_DISPOSITION)
    {
        insert_piece(pt, BLACK, piece_index_start);
        insert_piece(PAWN, BLACK, piece_index_start + dimension);
        insert_piece(pt, WHITE, piece_index_end);
        insert_piece(PAWN, WHITE, piece_index_end - dimension);
        nb_b_pieces += 2;
        nb_w_pieces += 2;
        piece_index_start++;
        piece_index_end--;
    }
}

void Board::set_space_style(const Color color, const size_t index, int& nb_styles_push)
{
    if (possible_spaces.find(index) != possible_spaces.end() && possible_spaces[index])
    {
        ImGui::PushStyleColor(ImGuiCol_Button, colors.ENEMY_SCOPE);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, colors.ENEMY_SCOPE_HOVERED);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, colors.ENEMY_SCOPE_ACTIVE);
        nb_styles_push += 3;
    }
    else
    {
        ImGui::PushStyleColor(ImGuiCol_Button, (color == WHITE) ? colors.WHITE_SPACE : colors.BLACK_SPACE);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (color == WHITE) ? colors.WHITE_SPACE_HOVERED : colors.BLACK_SPACE_HOVERED);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, (color == WHITE) ? colors.WHITE_SPACE_ACTIVE : colors.BLACK_SPACE_ACTIVE);
        nb_styles_push += 3;
    }
}

void Board::set_color_scope(ImU32& color_scope, const bool is_enemy)
{
    color_scope = is_enemy ? colors.ENEMY_SCOPE_BORDER : colors.NORMAL_SCOPE_BORDER;
    if (ImGui::IsItemHovered())
    {
        color_scope = is_enemy ? colors.ENEMY_SCOPE_BORDER_HOVERED : colors.NORMAL_SCOPE_BORDER_HOVERED;
    }
    if (ImGui::IsItemActive())
    {
        color_scope = is_enemy ? colors.ENEMY_SCOPE_BORDER_ACTIVE : colors.NORMAL_SCOPE_BORDER_ACTIVE;
    }
}

void Board::set_border_thickness(ImVec2& button_min, ImVec2& button_max, float border_thickness)
{
    button_min.x += border_thickness * 0.5f;
    button_min.y += border_thickness * 0.5f;
    button_max.x -= border_thickness * 0.5f;
    button_max.y -= border_thickness * 0.5f;
}

void Board::set_scope(const size_t index)
{
    if (possible_spaces.find(index) != possible_spaces.end())
    {
        bool   is_enemy   = possible_spaces[index];
        ImVec2 button_min = ImGui::GetItemRectMin();
        ImVec2 button_max = ImGui::GetItemRectMax();
        ImU32  color_scope;

        set_color_scope(color_scope, is_enemy);

        float border_thickness{4.0f};
        set_border_thickness(button_min, button_max, border_thickness);

        ImGui::GetWindowDrawList()->AddRect(
            button_min,
            button_max,
            color_scope,
            0.0f,
            0,
            border_thickness + 1.0f
        );
    }
}

void Board::set_piece_style(const Piece* piece_ptr, const char*& space_label)
{
    if (piece_ptr)
    {
        (piece_ptr->get_color() == WHITE) ? ImGui::GetStyle().Colors[ImGuiCol_Text] = colors.WHITE_PIECE
                                          : ImGui::GetStyle().Colors[ImGuiCol_Text] = colors.BLACK_PIECE;
        space_label = piece_ptr->get_symbol();
    }
}

void Board::set_style(const size_t& index, Color color, int& nb_style_push, const Piece* p, const char*& space_label)
{
    set_space_style(color, index, nb_style_push);
    set_piece_style(spaces[index], space_label);
}

void Board::end_game(const Color loser)
{
    for (Piece*& p : spaces)
    {
        if (p && p->get_color() == loser)
        {
            p = nullptr;
        }
    }
}

void Board::no_action_button(const char* space_label)
{
    ImGui::Button(space_label, {SPACE_SIZE, SPACE_SIZE});
}

void Board::first_click_button(size_t index, const char* space_label, History& history)
{
    if (ImGui::Button(space_label, {SPACE_SIZE, SPACE_SIZE}))
    {
        selected_piece = spaces[index];
        possible_spaces.clear();
        history.nb_moves() > 0 ? selected_piece->seach_positions_can_move(spaces, possible_spaces, dimension, {history.moves.back().piece, {history.moves.back().from_index, history.moves.back().to_index}})
                               : selected_piece->seach_positions_can_move(spaces, possible_spaces, dimension, {nullptr, {0, 0}});
    }
}

void Board::classic_eat(size_t index, History& history)
{
    if (spaces[index] && spaces[index]->get_color() != selected_piece->get_color())
    {
        history.add_eaten_piece(spaces[index]);
        (spaces[index]->get_color() == WHITE) ? nb_w_pieces-- : nb_b_pieces--;
        if (std::string(spaces[index]->get_symbol()) == "l")
            end_game(spaces[index]->get_color());
    }
}

void Board::prise_en_passant(size_t index)
{
    (selected_piece->get_color() == WHITE) ? spaces[index + dimension] = nullptr : spaces[index - dimension] = nullptr;
    (selected_piece->get_color() == WHITE) ? nb_w_pieces-- : nb_b_pieces--;
}

void Board::eat_piece(size_t index, History& history)
{
    if (spaces[index] && spaces[index]->get_color() != selected_piece->get_color())
    {
        classic_eat(index, history);
    }
    if (!spaces[index] && possible_spaces[index])
    {
        prise_en_passant(index);
    }
}

void Board::pawn_to_queen(Piece*& selected_piece, const size_t index)
{
    if (std::string(selected_piece->get_symbol()) == "o")
    {
        if (index < dimension || index >= pow(dimension, 2) - dimension)
            selected_piece = new Queen(selected_piece->get_color(), selected_piece->get_position());
    }
}

void Board::move_piece(size_t index)
{
    selected_piece->move(spaces, index);
    selected_piece = nullptr;
    possible_spaces.clear();
}

void Board::second_click_button(size_t index, const char* space_label, History& history)
{
    if (ImGui::Button(space_label, {SPACE_SIZE, SPACE_SIZE}))
    {
        if (possible_spaces.find(index) != possible_spaces.end())
        {
            eat_piece(index, history);

            history.add_move({history.nb_moves() + 1, selected_piece, selected_piece->get_position(), index});

            pawn_to_queen(selected_piece, index);

            move_piece(index);

            handle_turn();
        }
    }
}

void Board::create_button(size_t index, const char* space_label, History& history)
{
    if (spaces[index] && spaces[index]->get_color() == turn)
        first_click_button(index, space_label, history);
    else
        (!selected_piece) ? no_action_button(space_label) : second_click_button(index, space_label, history);
    set_scope(index);
}

void Board::init()
{
    selected_piece = nullptr;
    fill_pieces();
}

void Board::update(History& history)
{
    render(history);
}

void Board::render(History& history)
{
    ImGuiIO& io = ImGui::GetIO();
    ImGui::PushFont(io.Fonts->Fonts[1]);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
    Color        tile_color{WHITE};
    unsigned int id{1};
    for (size_t i{0}; i < spaces.size(); i++)
    {
        int nb_style_push{0};

        const char* space_label = "";
        set_style(i, tile_color, nb_style_push, spaces[i], space_label);

        ImGui::PushID(id);
        create_button(i, space_label, history);
        ImGui::PopID();

        ImGui::PopStyleColor(nb_style_push);

        if (id % 8 != 0)
        {
            ImGui::SameLine();
            tile_color = (tile_color == WHITE) ? BLACK : WHITE;
        }

        id++;
    }
    ImGui::PopFont();
    ImGui::PopStyleVar(1);
}
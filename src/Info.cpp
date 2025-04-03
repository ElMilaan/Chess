#include "headers/Info.hpp"

void Info::update(const Board& board, History& history)
{
    current_turn_number = history.nb_moves();
    current_turn_color  = board.get_turn();
    selected_piece      = board.get_selected_piece();
    nb_b_piece          = board.get_nb_b_pieces();
    nb_w_piece          = board.get_nb_w_pieces();
}

void Info::render(const bool end_game, const Color winner)
{
    ImGuiIO& io                             = ImGui::GetIO();
    ImGui::GetStyle().Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    if (!end_game)
    {
        ImGui::Text("Turn number : %d", (int)current_turn_number);
        ImGui::Text("Turn color : %s", (current_turn_color == WHITE) ? "WHITE" : "BLACK");
        ImGui::Text("White pieces remaining : %i", nb_w_piece);
        ImGui::Text("Black pieces remaining : %i", nb_b_piece);
        ImGui::Text("Last Move : ");
        ImGui::SameLine();
        if (history.moves.size() > 0)
        {
            ImGui::PushFont(io.Fonts->Fonts[1]);
            ImGui::Text("%s : ", history.moves.back().piece->get_symbol());
            ImGui::PopFont();
            ImGui::SameLine();
            ImGui::Text("%zu -> %zu", history.moves.back().from_index, history.moves.back().to_index);
        }
        else
        {
            ImGui::Text("No move yet");
        }

        if (selected_piece)
        {
            ImGui::Text("Selected piece : ");
            ImGui::SameLine();
            ImGui::PushFont(io.Fonts->Fonts[1]);
            ImGui::Text("%s", selected_piece->get_symbol());
            ImGui::PopFont();
            ImGui::Text("Selected piece color : %s", (selected_piece->get_color() == WHITE) ? "WHITE" : "BLACK");
        }
        else
        {
            ImGui::Text("No piece selected");
        }
    }
    else
    {
        ImGui::Text("Game Over");
        winner == WHITE ? ImGui::Text("White wins !") : ImGui::Text("Black wins !");
        return;
    }
}
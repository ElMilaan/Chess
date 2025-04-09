#pragma once

#include <quick_imgui/quick_imgui.hpp>
#include <glm/glm.hpp>

enum Color
{
    WHITE,
    BLACK
};

struct ColorUI
{
    ImVec4 WHITE_SPACE{0.87f, 0.72f, 0.53f, 1.0f};
    ImVec4 WHITE_SPACE_HOVERED{0.79f, 0.64f, 0.45f, 1.0f};
    ImVec4 WHITE_SPACE_ACTIVE{0.73f, 0.58f, 0.40f, 1.0f};

    ImVec4 NORMAL_SCOPE{0.50f, 0.50f, 0.50f, 1.0f};
    ImVec4 NORMAL_SCOPE_HOVERED{0.30f, 0.30f, 0.30f, 1.0f};
    ImVec4 NORMAL_SCOPE_ACTIVE{0.20f, 0.20f, 0.20f, 1.0f};

    ImU32 NORMAL_SCOPE_BORDER{IM_COL32(255, 255, 255, 255)};
    ImU32 NORMAL_SCOPE_BORDER_HOVERED{IM_COL32(180, 180, 180, 255)};
    ImU32 NORMAL_SCOPE_BORDER_ACTIVE{IM_COL32(130, 130, 130, 255)};

    ImVec4 ENEMY_SCOPE{0.80f, 0.05f, 0.05f, 1.0f};
    ImVec4 ENEMY_SCOPE_HOVERED{0.60, 0.05f, 0.05f, 1.0f};
    ImVec4 ENEMY_SCOPE_ACTIVE{0.40f, 0.0f, 0.0f, 1.0f};

    ImU32 ENEMY_SCOPE_BORDER{IM_COL32(0, 0, 0, 255)};
    ImU32 ENEMY_SCOPE_BORDER_HOVERED{IM_COL32(75, 0, 0, 255)};
    ImU32 ENEMY_SCOPE_BORDER_ACTIVE{IM_COL32(45, 0, 0, 255)};

    ImVec4 BLACK_SPACE{0.47f, 0.27f, 0.20f, 1.0f};
    ImVec4 BLACK_SPACE_HOVERED{0.39f, 0.19f, 0.12f, 1.0f};
    ImVec4 BLACK_SPACE_ACTIVE{0.34f, 0.14f, 0.07f, 1.0f};

    ImVec4 WHITE_PIECE{1.0f, 1.0f, 1.0f, 1.0f};
    ImVec4 BLACK_PIECE{0.0f, 0.0f, 0.0f, 1.0f};
};

glm::vec3 chess_id_to_opengl_coords(int id);
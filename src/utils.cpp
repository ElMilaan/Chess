#include "headers/utils.hpp"

glm::vec3 chess_id_to_opengl_coords(int id)
{
    int row = id / 8;
    int col = id % 8;

    float x = (col - 3.5f);
    float y = (3.5f - row);

    return glm::vec3(x, y, 0.0f);
    // regarder la hauteur du plateau et changer le 0
}
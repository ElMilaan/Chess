#include "headers/utils.hpp"

glm::vec3 position_2D_to_3D(int id) {
  int row = id / 8;
  int col = id % 8;

  float abs = (col - 3.5f);
  float ord = (3.5f - row);

  return glm::vec3(abs, 0.0f, ord);
  // regarder la hauteur du plateau et changer le 0
}

void gl_clear() {
  glClearColor(0.847f, 0.82f, 0.929f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
}
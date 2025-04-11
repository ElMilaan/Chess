#pragma once

#include "Board.hpp"
#include "Camera.hpp"
#include "Model3D.hpp"
#include "headers/Skybox.hpp"
#include <iostream>

class Renderer3D {

private:
  std::map<std::string, Model3D *> models{};
  glmax::Shader shader;
  glmax::Camera camera{true};
  Skybox skybox{};

public:
  Renderer3D() = default;

  glmax::Camera get_camera() const;
  void camera_zoom(float zoom);
  void camera_move(double xpos, double ypos);

  void init();
  void set_models(const std::string &directory_path);
  void load_meshes();
  void load_shader(const std::string &vs, const std::string &fs);
  void set_id_matrix();
  void loop_shader(glm::mat4 board_projection);

  void render(Board *board, glm::mat4 board_projection,
              glm::mat4 skybox_projection);

  void render_board(glm::mat4 board_projection);

  void render_piece(const Piece *&piece);
  void render_pieces(Board *&board, const glm::mat4 &board_projection);
};

std::ostream &
operator<<(std::ostream &os,
           const std::vector<std::pair<Model3D *, std::string>> &models);

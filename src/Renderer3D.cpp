#include "headers/Renderer3D.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/trigonometric.hpp"
#include "headers/Board.hpp"
#include "headers/Skybox.hpp"
#include "headers/utils.hpp"
#include <filesystem>
#include <string>

glmax::Camera Renderer3D::get_camera() const { return camera; }

void Renderer3D::camera_zoom(float zoom) { camera.process_scroll(zoom); }

void Renderer3D::camera_move(double xpos, double ypos) {
  camera.track_ball_move_callback(xpos, ypos);
}

void Renderer3D::init() {
  // skybox.init();
  set_models("assets/models");
  load_shader("model.vs.glsl", "model.fs.glsl");
  load_meshes();
}

std::string format_obj_path(const std::string &name) {
  return name + "/" + name + ".obj";
}

void Renderer3D::load_shader(const std::string &vs, const std::string &fs) {
  shader.load_shader(vs, fs);
}

void Renderer3D::loop_shader(glm::mat4 board_projection) {
  shader.use();

  glm::mat4 id_matrix = glm::mat4(1.0f);
  shader.set_uniform_matrix_4fv("model", id_matrix);

  shader.set_uniform_matrix_4fv("view", camera.get_view_matrix());
  shader.set_uniform_matrix_4fv("projection", board_projection);

  shader.set_uniform_3fv("lightPos", glm::vec3(5.0f, 5.0f, 5.0f));
  shader.set_uniform_3fv("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

  shader.set_uniform_3fv("viewPos", camera.get_position());
}

void Renderer3D::load_meshes() {
  for (std::pair<const std::string, Model3D *> &model : models) {
    model.second->load_mesh(format_obj_path(model.first), model.first);
    model.second->setup_buffers();
    std::cout << "";
  }
}

void Renderer3D::set_models(const std::string &directory_path) {
  for (const std::filesystem::directory_entry &entry :
       std::filesystem::directory_iterator(directory_path)) {
    if (entry.is_directory()) {
      models.insert({entry.path().filename().string(), new Model3D()});
    }
  }
}

void Renderer3D::set_id_matrix() {
  for (const std::pair<std::string, Model3D *> &model : models) {
  }
}

void Renderer3D::render(Board *board, glm::mat4 board_projection,
                        glm::mat4 skybox_projection) {
  // skybox.render(camera.get_view_matrix(), skybox_projection);
  render_board(board_projection);
  render_pieces(board, board_projection);
}

void Renderer3D::render_board(glm::mat4 board_projection) {
  loop_shader(board_projection);
  models.at("Chess_Board")->render(shader, false);
}

void Renderer3D::render_piece(const Piece *&piece) {
  if (dynamic_cast<const Bishop *>(piece))
    models.at("Bishop")->render(shader, piece->get_color() == BLACK);
  else if (dynamic_cast<const Pawn *>(piece))
    models.at("Pawn")->render(shader, piece->get_color() == BLACK);
  else if (dynamic_cast<const King *>(piece))
    models.at("King")->render(shader, piece->get_color() == BLACK);
  else if (dynamic_cast<const Queen *>(piece))
    models.at("Queen")->render(shader, piece->get_color() == BLACK);
  else if (dynamic_cast<const Rook *>(piece))
    models.at("Rook")->render(shader, piece->get_color() == BLACK);
  else if (dynamic_cast<const Knight *>(piece))
    models.at("Knight")->render(shader, piece->get_color() == BLACK);
}

void Renderer3D::render_pieces(Board *&board,
                               const glm::mat4 &board_projection) {
  shader.use();
  shader.set_uniform_matrix_4fv("projection", board_projection);

  const std::vector<Piece *> &spaces = board->get_spaces();

  for (size_t i = 0; i < spaces.size(); ++i) {
    const Piece *piece = spaces[i];
    if (piece) {
      glm::vec3 position = position_2D_to_3D(i);
      glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
      if (piece->get_color() == BLACK) {
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 0));
      }

      shader.set_uniform_matrix_4fv("model", model);

      render_piece(piece);
    }
  }
}

std::ostream &
operator<<(std::ostream &os,
           const std::vector<std::pair<Model3D *, std::string>> &models) {
  os << "Models: " << std::endl;
  for (const std::pair<Model3D *, std::string> &model : models) {
    os << model.second << std::endl;
  }
  return os;
}
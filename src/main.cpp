#include "glm/ext/matrix_clip_space.hpp"
#include "headers/App.hpp"
#include "headers/Renderer3D.hpp"
#include "headers/utils.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <quick_imgui/quick_imgui.hpp>
#include <stdio.h>

int main() {
  int window_width = 1280;
  int window_height = 720;
  bool left_clicked = false;

  Renderer3D *renderer = new Renderer3D();

  App *app = new App(8);

  quick_imgui::loop(
      "Chess",
      {
          .init =
              [&]() {
                app->init();
                renderer->init();
              },

          .loop =
              [&]() {
                app->run();
                gl_clear();
                glm::mat4 board_projection =
                    glm::perspective(glm::radians(45.0f),
                                     static_cast<float>(window_width) /
                                         static_cast<float>(window_height),
                                     0.1f, 100.0f);
                glm::mat4 skybox_projection =
                    glm::perspective(glm::radians(45.0f),
                                     static_cast<float>(window_width) /
                                         static_cast<float>(window_height),
                                     1.0f, 100.0f);
                renderer->render(app->get_board(), board_projection,
                                 skybox_projection);
              },

          .key_callback =
              [&](int key, int scancode, int action, int mods) {
                std::cout << "Key: " << key << " Scancode: " << scancode
                          << " Action: " << action << " Mods: " << mods << '\n';
              },
          .mouse_button_callback =
              [&](int button, int action, int mods) {
                if (button == 0 && action == 1) {
                  left_clicked = true;
                } else if (button == 0 && action == 0) {
                  left_clicked = false;
                }
                std::cout << "Button: " << button << " Action: " << action
                          << " Mods: " << mods << '\n';
              },
          .cursor_position_callback =
              [&](double xpos, double ypos) {
                if (left_clicked)
                  renderer->camera_move(xpos, ypos);
              },
          .scroll_callback =
              [&](double xoffset, double yoffset) {
                renderer->camera_zoom(yoffset);
              },
          .window_size_callback =
              [&](int width, int height) {
                std::cout << "Resized: " << width << ' ' << height << '\n';
              },
      });
  return 0;
}
#include <stdio.h>
#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <quick_imgui/quick_imgui.hpp>
#include "Camera.hpp"
#include "Shader.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "headers/App.hpp"
#include "headers/Model3D.hpp"

int main()
{
    int           window_width  = 1280;
    int           window_height = 720;
    glmax::Shader shader;
    glmax::Camera camera{true};

    Model3D model;

    App* app = new App(8);

    quick_imgui::loop("Chess", {
                                   .init                     = [&]() {  app->init();
                                                    shader.load_shader("model.vs.glsl", "model.fs.glsl");
                                                    model.load_mesh("King/white_king.obj", "King");
                                                    model.setup_buffers(); },
                                   .loop                     = [&]() {
                                    app->run();
                                    glClearColor(0.847f, 0.82f, 0.929f, 1.f);
                                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                                    glEnable(GL_DEPTH_TEST);

                                    glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(window_width) / static_cast<float>(window_height), 0.1f, 100.0f);
                                    shader.use();

                                    // MVP
                                    shader.set_uniform_matrix_4fv("model", glm::mat4(1.0f));
                                    shader.set_uniform_matrix_4fv("view", camera.get_view_matrix());
                                    shader.set_uniform_matrix_4fv("projection", projection);
                                    // LIGHT SETTINGS
                                    shader.set_uniform_3fv("lightPos", glm::vec3(5.0f, 5.0f, 5.0f));
                                    shader.set_uniform_3fv("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
                                    // CAMERA SETTINGS
                                    shader.set_uniform_3fv("viewPos", camera.get_position());

                                    // MODEL RENDER
                                    model.render(shader); },
                                   .key_callback             = [&](int key, int scancode, int action, int mods) { std::cout << "Key: " << key << " Scancode: " << scancode << " Action: " << action << " Mods: " << mods << '\n'; },
                                   .mouse_button_callback    = [&](int button, int action, int mods) { std::cout << "Button: " << button << " Action: " << action << " Mods: " << mods << '\n'; },
                                   .cursor_position_callback = [&](double xpos, double ypos) { camera.track_ball_move_callback(xpos, ypos); },
                                   .scroll_callback          = [&](double xoffset, double yoffset) { camera.process_scroll(yoffset); },
                                   .window_size_callback     = [&](int width, int height) { std::cout << "Resized: " << width << ' ' << height << '\n'; },
                               });
    return 0;
}
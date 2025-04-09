#pragma once

#include "Model3D.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include <filesystem>
#include <iostream>

class Renderer3D
{

private:
    std::vector<std::pair<Model3D *, std::string>> models{};
    glmax::Shader shader;
    glmax::Camera camera{true};

public:
    Renderer3D() = default;

    glmax::Camera get_camera() const;
    void camera_zoom(float zoom);
    void camera_move(double xpos, double ypos);

    void init();
    void set_models(const std::string &directory_path);
    void load_meshes();
    void load_shader(const std::string &vs, const std::string &fs);
    void render(glm::mat4 projection);
    void set_id_matrix();
    void loop_shader(glm::mat4 projection);
};

std::ostream &operator<<(std::ostream &os, const std::vector<std::pair<Model3D *, std::string>> &models);

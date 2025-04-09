#pragma once

#include <string>
#include "Mesh.hpp"
#include "Shader.hpp"
#include "buffers/EBO.hpp"
#include "buffers/VAO.hpp"
#include "buffers/VBO.hpp"

class Model3D
{
public:
    Model3D() = default;
    void load_mesh(const std::string &path, const std::string &name);
    void setup_buffers();

    void render(glmax::Shader &shader) const;

private:
    // single mesh
    glmax::Mesh m_mesh;

    // Buffers
    VAO m_vao;
    VBO m_vbo;
    EBO m_ebo;
};
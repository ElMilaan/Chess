#pragma once

#include "Mesh.hpp"
#include "Shader.hpp"
#include "buffers/EBO.hpp"
#include "buffers/VAO.hpp"
#include "buffers/VBO.hpp"
#include <string>

class Model3D {
public:
  Model3D() = default;
  void load_mesh(const std::string &path, const std::string &name);
  void setup_buffers();
  void set_material(glmax::Shader &shader, const glmax::Material &material,
                    const glm::vec3 &color) const;
  void materials_uniform(glmax::Shader &shader, const glmax::Material &material,
                         bool black) const;
  void render(glmax::Shader &shader, bool black) const;

private:
  // single mesh
  glmax::Mesh m_mesh;

  // Buffers
  VAO m_vao;
  VBO m_vbo;
  EBO m_ebo;
};
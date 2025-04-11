#pragma once

#include "Shader.hpp"
#include "Texture.hpp"
#include "buffers/VAO.hpp"
#include "buffers/VBO.hpp"
#include <glm/glm.hpp>
#include <string>
#include <vector>

class Skybox {
public:
  Skybox() = default;
  void init();
  void render(const glm::mat4 &view, const glm::mat4 &projection);

private:
  std::vector<std::string> m_cubemap_faces{
      "assets/textures/skybox/right.jpg", "assets/textures/skybox/left.jpg",
      "assets/textures/skybox/top.jpg",   "assets/textures/skybox/bottom.jpg",
      "assets/textures/skybox/front.jpg", "assets/textures/skybox/back.jpg"};
  glmax::Shader m_shader;
  glmax::Texture m_texture;
  VAO m_vao;
  VBO m_vbo;
};

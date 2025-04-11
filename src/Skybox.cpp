#include "headers/Skybox.hpp"

void Skybox::init() {

  m_shader.load_shader("skybox.vs.glsl", "skybox.fs.glsl");
  m_texture.load_cubemap(m_cubemap_faces);

  float skyboxVertices[] = {
      -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f,
      1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f,

      -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f,
      -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,

      1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,
      1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f,

      -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
      1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,

      -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,
      1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f,

      -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f,
      1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,
  };

  m_vao.init();
  m_vbo.init();
  m_vao.bind();
  m_vbo.bind();
  m_vbo.set_data(skyboxVertices, sizeof(skyboxVertices));
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
}

void Skybox::render(const glm::mat4 &view, const glm::mat4 &projection) {
  glDepthFunc(GL_LEQUAL);
  m_shader.use();
  glm::mat4 viewNoTranslation = glm::mat4(glm::mat3(view));
  m_shader.set_uniform_matrix_4fv("view", viewNoTranslation);
  m_shader.set_uniform_matrix_4fv("projection", projection);

  m_vao.bind();
  m_texture.bind(m_texture.getID());
  glDrawArrays(GL_TRIANGLES, 0, 36);
  m_vao.unbind();

  glDepthFunc(GL_LESS);
}
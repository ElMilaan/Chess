#include "headers/Model3D.hpp"
#include "Material.hpp"
#include "glm/fwd.hpp"

void Model3D::load_mesh(const std::string &path, const std::string &name) {
  m_mesh.load(path, name);
}

void Model3D::setup_buffers() {
  m_vbo.init();
  m_vbo.bind();
  m_vbo.set_data(m_mesh.get_vertices().data(),
                 m_mesh.get_vertices().size() * sizeof(glmax::Vertex));
  m_vbo.unbind();

  m_ebo.init();
  m_ebo.bind();
  m_ebo.set_data(m_mesh.get_indices().data(),
                 m_mesh.get_indices().size() * sizeof(uint32_t));
  m_ebo.unbind();

  m_vao.init();
  m_vao.bind();
  m_vbo.bind();
  m_ebo.bind();

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glmax::Vertex),
                        (const GLvoid *)offsetof(glmax::Vertex, m_position));

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glmax::Vertex),
                        (const GLvoid *)offsetof(glmax::Vertex, m_normal));

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glmax::Vertex),
                        (const GLvoid *)offsetof(glmax::Vertex, m_tex_coord));

  m_vao.unbind();
}

void Model3D::set_material(glmax::Shader &shader,
                           const glmax::Material &material,
                           const glm::vec3 &color) const {
  shader.set_uniform_3fv("Kd", color);
  shader.set_uniform_3fv("Ka", material.m_Ka);
  shader.set_uniform_3fv("Ks", material.m_Ks);
  shader.set_uniform_1f("Ns", material.m_Ns);
}

void Model3D::materials_uniform(glmax::Shader &shader,
                                const glmax::Material &material,
                                bool black) const {
  set_material(shader, material, black ? glm::vec3(0.2f) : material.m_Kd);

  if (material.m_hasMapKd) {
    shader.set_uniform_1i("map_Kd", material.m_mapKd.getID());
    material.m_mapKd.bind(material.m_mapKd.getID());
    shader.set_uniform_1i("useTexture", true);
  } else {
    shader.set_uniform_1i("useTexture", false);
  }
}

void Model3D::render(glmax::Shader &shader, bool black) const {
  m_vao.bind();

  for (const glmax::Submesh &submesh : m_mesh.get_submeshes()) {
    const glmax::Material &material =
        m_mesh.get_materials().at(submesh.m_material_id);

    materials_uniform(shader, material, black);

    glDrawElements(GL_TRIANGLES, submesh.m_index_count, GL_UNSIGNED_INT,
                   (const GLvoid *)(submesh.m_index_offset * sizeof(uint32_t)));

    if (material.m_hasMapKd)
      material.m_mapKd.unbind();
  }

  m_vao.unbind();
}
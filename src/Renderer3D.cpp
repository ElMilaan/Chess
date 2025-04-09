#include "headers/Renderer3D.hpp"

glmax::Camera Renderer3D::get_camera() const
{
    return camera;
}

void Renderer3D::camera_zoom(float zoom)
{
    camera.process_scroll(zoom);
}

void Renderer3D::camera_move(double xpos, double ypos)
{
    camera.track_ball_move_callback(xpos, ypos);
}

void Renderer3D::init()
{
    set_models("assets/models");
    load_shader("model.vs.glsl", "model.fs.glsl");
    load_meshes();
}

std::string format_obj_path(const std::string &name)
{
    return name + "/" + name + ".obj";
}

void Renderer3D::load_shader(const std::string &vs, const std::string &fs)
{
    shader.load_shader(vs, fs);
}

void Renderer3D::loop_shader(glm::mat4 projection)
{
    shader.use();

    glm::mat4 id_matrix = glm::mat4(1.0f);
    shader.set_uniform_matrix_4fv("model", id_matrix);

    shader.set_uniform_matrix_4fv("view", camera.get_view_matrix());
    shader.set_uniform_matrix_4fv("projection", projection);

    shader.set_uniform_3fv("lightPos", glm::vec3(5.0f, 5.0f, 5.0f));
    shader.set_uniform_3fv("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

    shader.set_uniform_3fv("viewPos", camera.get_position());
}

void Renderer3D::load_meshes()
{
    for (std::pair<Model3D *, std::string> &model : models)
    {
        model.first->load_mesh(format_obj_path(model.second), model.second);
        model.first->setup_buffers();
        std::cout << "";
    }
}

void Renderer3D::set_models(const std::string &directory_path)
{
    for (const auto &entry : std::filesystem::directory_iterator(directory_path))
    {
        if (entry.is_directory())
        {
            models.push_back({new Model3D(), entry.path().filename().string()});
        }
    }
}

void Renderer3D::set_id_matrix()
{
    for (const std::pair<Model3D *, std::string> &model : models)
    {
    }
}

void Renderer3D::render(glm::mat4 projection)
{
    for (const std::pair<Model3D *, std::string> &model : models)
    {
        loop_shader(projection);
        std::cout
            << "Model rendered: " << model.second << std::endl;
        model.first->render(shader);
    }
}

std::ostream &operator<<(std::ostream &os, const std::vector<std::pair<Model3D *, std::string>> &models)
{
    os << "Models: " << std::endl;
    for (const auto &model : models)
    {
        os << model.second << std::endl;
    }
    return os;
}
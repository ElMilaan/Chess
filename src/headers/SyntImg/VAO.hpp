#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>

struct VAO {
    GLuint id;
    VAO(GLuint id);
    void bind();
    void unbind();
    ~VAO();
};
#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "headers/SyntImg/VAO.hpp"

VAO::VAO(GLuint id)
{
    id = id;
    glGenVertexArrays(1, &id);
}
void VAO::bind()
{
    glBindVertexArray(id);
}
void VAO::unbind()
{
    glBindVertexArray(0);
}
VAO::~VAO()
{
    glDeleteVertexArrays(1, &id);
}
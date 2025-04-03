#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "headers/SyntImg/VBO.hpp"

VBO::VBO()
{
    glGenBuffers(1, &id);
}

void VBO::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VBO::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::setData(GLsizeiptr size, const void* data, GLenum usage)
{
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void VBO::setSubData(GLintptr offset, GLsizeiptr size, const void* data)
{
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void VBO::destroy()
{
    glDeleteBuffers(1, &id);
}
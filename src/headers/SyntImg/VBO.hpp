#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>

struct VBO {
    GLuint id;
    VBO()
    {
        glGenBuffers(1, &id);
    }
    void bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }
    void unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    void setData(GLsizeiptr size, const void* data, GLenum usage)
    {
        glBufferData(GL_ARRAY_BUFFER, size, data, usage);
    }
    void setSubData(GLintptr offset, GLsizeiptr size, const void* data)
    {
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
    }
    void destroy()
    {
        glDeleteBuffers(1, &id);
    }
};
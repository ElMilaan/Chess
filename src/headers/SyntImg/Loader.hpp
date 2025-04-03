#pragma once
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

struct Vertex {
    float pos[3];
    float norm[3];
    float tex_coords[2];
};

namespace Loader {
bool loadModel(const std::string& path, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
} // namespace Loader

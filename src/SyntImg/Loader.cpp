
#include "headers/SyntImg/Loader.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

bool Loader::loadModel(const std::string& path, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
    tinyobj::attrib_t                attrib;
    std::vector<tinyobj::shape_t>    shapes;
    std::vector<tinyobj::material_t> materials;
    std::string                      warn;
    std::string                      err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str());

    if (!err.empty())
    {
        std::cerr << "TinyObjLoader Error: " << err << std::endl;
    }

    if (!ret)
    {
        return false;
    }
    for (const auto& shape : shapes)
    {
        for (const auto& index : shape.mesh.indices)
        {
            Vertex vertex = {};

            vertex.pos[0] = attrib.vertices[3 * index.vertex_index + 0];
            vertex.pos[1] = attrib.vertices[3 * index.vertex_index + 1];
            vertex.pos[2] = attrib.vertices[3 * index.vertex_index + 2];

            if (index.normal_index >= 0)
            {
                vertex.norm[0] = attrib.normals[3 * index.normal_index + 0];
                vertex.norm[1] = attrib.normals[3 * index.normal_index + 1];
                vertex.norm[2] = attrib.normals[3 * index.normal_index + 2];
            }

            if (index.texcoord_index >= 0)
            {
                vertex.tex_coords[0] = attrib.texcoords[2 * index.texcoord_index + 0];
                vertex.tex_coords[1] = attrib.texcoords[2 * index.texcoord_index + 1];
            }

            vertices.push_back(vertex);
            indices.push_back(indices.size());
        }
    }

    return true;
}

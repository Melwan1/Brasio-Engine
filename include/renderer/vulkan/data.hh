#pragma once

#include <geometry/vertex.hh>
#include <vector>

std::vector<brasio::geometry::Vertex> vertices_data = {
    //        position                color
    { { -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { { +0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f } },
    { { +0.5f, -0.5f, 1.0f }, { 1.0f, 0.0f, 1.0f } },
    { { -0.5f, -0.5f, 1.0f }, { 0.0f, 0.0f, 1.0f } },
    { { -0.5f, +0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f } },
    { { +0.5f, +0.5f, 0.0f }, { 1.0f, 1.0f, 0.0f } },
    { { +0.5f, +0.5f, 1.0f }, { 1.0f, 1.0f, 1.0f } },
    { { -0.5f, +0.5f, 1.0f }, { 0.0f, 1.0f, 1.0f } },
};

std::vector<uint16_t> indices_data = {
    0, 1, 2, // bottom face first triangle
    2, 3, 0, // bottom face second triangle
    7, 6, 5, // top face first triangle
    5, 4, 7, // top face second triangle
    4, 5, 1, // front face first triangle
    1, 0, 4, // front face second triangle
    5, 6, 2, // right face first triangle
    2, 1, 5, // right face second triangle
    6, 7, 3, // back face first triangle
    3, 2, 6, // back face second triangle
    7, 4, 0, // left face first triangle
    0, 3, 7, // left face second triangle
};

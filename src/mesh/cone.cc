#include <mesh/cone.hh>

#include <numbers>

namespace brasio::mesh
{

    Cone::Cone(int base_tessellation, float height)
        : Mesh(Cone::build(base_tessellation, height))
    {}

    std::pair<std::vector<geometry::Vertex>, std::vector<uint16_t>>
    Cone::build(int base_tessellation, float height)
    {
        std::vector<geometry::Vertex> vertices;
        std::vector<uint16_t> indices;

        // top = 0, base center = 1, then (base_tessellation + 1) vertices for
        // the base from 2 to (base_tessellation + 2) inclusive
        vertices.reserve(base_tessellation + 3);

        // base_tessellation lateral faces + base_tessellation base faces, 3
        // vertices per face (1 face = 1 triangle)
        indices.reserve(base_tessellation * 2 * 3 * 2);

        // top vertex
        vertices.emplace_back(
            geometry::Vertex({ 0.0f, height, 0.0f }, { 0.5f, 0.5f, 0.5f }));

        // base center vertex
        vertices.emplace_back(
            geometry::Vertex({ 0.0f, 0.0f, 0.0f }, { 0.5f, 0.5f, 0.5f }));

        for (int base_tessellation_index = 0;
             base_tessellation_index <= base_tessellation;
             base_tessellation_index++)
        {
            // rest of base vertex
            vertices.emplace_back(geometry::Vertex(
                { 0.5f
                      * std::cos(static_cast<float>(base_tessellation_index)
                                 / base_tessellation * 2 * std::numbers::pi),
                  0.0f,
                  0.5f
                      * std::sin(static_cast<float>(base_tessellation_index)
                                 / base_tessellation * 2 * std::numbers::pi) },
                { 0.5f, 0.5f, 0.5f }));

            // lateral triangle
            indices.emplace_back(base_tessellation_index + 2);
            indices.emplace_back(
                (base_tessellation_index + 1) % (base_tessellation + 1) + 2);
            indices.emplace_back(0);

            // base triangle
            indices.emplace_back(
                (base_tessellation_index + 1) % (base_tessellation + 1) + 2);
            indices.emplace_back(base_tessellation_index + 2);
            indices.emplace_back(1);
        }
        return std::make_pair<>(vertices, indices);
    }
} // namespace brasio::mesh

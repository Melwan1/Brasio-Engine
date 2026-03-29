#include <mesh/cylinder.hh>

namespace brasio::mesh
{

    Cylinder::Cylinder(int lateral_tessellation)
        : Mesh(Cylinder::build(lateral_tessellation))
    {}

    std::pair<std::vector<geometry::Vertex>, std::vector<uint16_t>>
    Cylinder::build(int lateral_tessellation)
    {
        std::vector<geometry::Vertex> vertices;
        std::vector<uint16_t> indices;

        // 2 * lateral_tessellation vertices on both base disks
        // + 1 vertex on each disk base center
        vertices.reserve(2 * lateral_tessellation + 2);

        // 1 lateral face (= 2 triangles) per lateral_tessellation + 1 base
        // triangle per lateral_tessellation for each base (= 2 triangles)
        indices.reserve(4 * 3 * lateral_tessellation);

        vertices.emplace_back(
            geometry::Vertex({ 0.0f, 0.0f, 0.0f }, { 0.5f, 0.5f, 0.5f }));
        vertices.emplace_back(
            geometry::Vertex({ 0.0f, 1.0f, 0.0f }, { 0.5f, 0.5f, 0.5f }));

        for (int lateral_tessellation_index = 0;
             lateral_tessellation_index < lateral_tessellation;
             lateral_tessellation_index++)
        {
            float angle = 2 * std::numbers::pi
                * static_cast<float>(lateral_tessellation_index)
                / lateral_tessellation;
            vertices.emplace_back(geometry::Vertex(
                { 0.5f * std::cos(angle), 0.0f, 0.5f * std::sin(angle) },
                { 0.5f, 0.5f, 0.5f }));
            vertices.emplace_back(geometry::Vertex(
                { 0.5f * std::cos(angle), 1.0f, 0.5f * std::sin(angle) },
                { 0.5f, 0.5f, 0.5f }));

            // bottom triangle
            indices.emplace_back(2 * (lateral_tessellation_index + 1));
            indices.emplace_back(
                2
                * ((lateral_tessellation_index + 1) % lateral_tessellation
                   + 1));
            indices.emplace_back(0);

            // top triangle
            indices.emplace_back(2 * (lateral_tessellation_index + 1) + 1);
            indices.emplace_back(
                2
                    * ((lateral_tessellation_index + 1) % lateral_tessellation
                       + 1)
                + 1);
            indices.emplace_back(1);

            // lateral face
            indices.emplace_back(2 * (lateral_tessellation_index + 1));
            indices.emplace_back(
                2
                * ((lateral_tessellation_index + 1) % lateral_tessellation
                   + 1));
            indices.emplace_back(
                2
                    * ((lateral_tessellation_index + 1) % lateral_tessellation
                       + 1)
                + 1);
            indices.emplace_back(
                2
                    * ((lateral_tessellation_index + 1) % lateral_tessellation
                       + 1)
                + 1);
            indices.emplace_back(2 * (lateral_tessellation_index + 1) + 1);
            indices.emplace_back(2 * (lateral_tessellation_index + 1));
        }

        return std::make_pair(vertices, indices);
    }

} // namespace brasio::mesh

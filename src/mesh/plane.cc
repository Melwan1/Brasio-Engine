#include <mesh/plane.hh>

namespace brasio::mesh
{

    Plane::Plane(int horizontal_tessellation, int vertical_tessellation)
        : Mesh(Plane::build(horizontal_tessellation, vertical_tessellation))
    {}

    std::pair<std::vector<geometry::Vertex>, std::vector<uint16_t>>
    Plane::build(int horizontal_tessellation, int vertical_tessellation)
    {
        std::vector<geometry::Vertex> vertices;
        std::vector<uint16_t> indices;
        vertices.reserve((horizontal_tessellation + 1)
                         * (vertical_tessellation + 1));
        indices.reserve(
            horizontal_tessellation * vertical_tessellation * 2
            * 3); // three indices per triangle, 2 triangles per face

        for (int vertical_tessellation_index = 0;
             vertical_tessellation_index <= vertical_tessellation;
             vertical_tessellation_index++)
        {
            for (int horizontal_tessellation_index = 0;
                 horizontal_tessellation_index <= horizontal_tessellation;
                 horizontal_tessellation_index++)
            {
                vertices.emplace_back(geometry::Vertex(
                    { static_cast<float>(horizontal_tessellation_index)
                              / horizontal_tessellation
                          - 0.5f,
                      0.0f,
                      static_cast<float>(vertical_tessellation_index)
                              / vertical_tessellation
                          - 0.5f },
                    { 0.5f, 0.5f, 0.5f }));
                if (horizontal_tessellation_index > 0
                    && vertical_tessellation_index > 0)
                {
                    indices.emplace_back(vertical_tessellation_index
                                             * (horizontal_tessellation + 1)
                                         + horizontal_tessellation_index - 1);
                    indices.emplace_back(vertical_tessellation_index
                                             * (horizontal_tessellation + 1)
                                         + horizontal_tessellation_index);
                    indices.emplace_back((vertical_tessellation_index - 1)
                                             * (horizontal_tessellation + 1)
                                         + horizontal_tessellation_index);
                    indices.emplace_back((vertical_tessellation_index - 1)
                                             * (horizontal_tessellation + 1)
                                         + horizontal_tessellation_index);
                    indices.emplace_back((vertical_tessellation_index - 1)
                                             * (horizontal_tessellation + 1)
                                         + horizontal_tessellation_index - 1);
                    indices.emplace_back(vertical_tessellation_index
                                             * (horizontal_tessellation + 1)
                                         + horizontal_tessellation_index - 1);
                }
            }
        }
        return std::make_pair<>(vertices, indices);
    }

} // namespace brasio::mesh

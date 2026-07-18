#include <mesh/triangle.hh>

namespace brasio::mesh
{

    Triangle::Triangle()
        : Mesh(Triangle::build())
    {}

    std::pair<std::vector<geometry::Vertex>, std::vector<uint16_t>>
    Triangle::build()
    {
        return { { { { -0.5f, 0.0f, 0.0f } },
                   { { 0.5f, 0.0f, 0.0f } },
                   { { 0.0f, 1.0f, 0.0f } } },
                 { 0, 1, 2 } };
    }
} // namespace brasio::mesh

#pragma once

#include <mesh/mesh.hh>

namespace brasio::mesh
{

    class Triangle : public Mesh
    {
    public:
        Triangle();
        static std::pair<std::vector<geometry::Vertex>, std::vector<IndexType>>
        build();
    };
} // namespace brasio::mesh

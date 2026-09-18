#pragma once

#include <mesh/mesh.hh>

#include <mesh/mesh.hh>

namespace brasio::mesh
{

    class Sphere : public Mesh
    {
    public:
        Sphere(unsigned n_slices, unsigned n_stacks);

        static std::pair<std::vector<geometry::Vertex>, std::vector<IndexType>>
        build(unsigned n_slices, unsigned n_stacks);
    };
} // namespace brasio::mesh

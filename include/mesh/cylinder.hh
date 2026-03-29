#pragma once

#include <mesh/mesh.hh>

#define BRASIO_MESH_CYLINDER_DEFAULT_LATERAL_TESSELLATION 32

namespace brasio::mesh
{

    class Cylinder : public Mesh
    {
    public:
        Cylinder(int lateral_tessellation =
                     BRASIO_MESH_CYLINDER_DEFAULT_LATERAL_TESSELLATION);

        static std::pair<std::vector<geometry::Vertex>, std::vector<uint16_t>>
        build(int lateral_tessellation);
    };

} // namespace brasio::mesh

#pragma once

#include <mesh/mesh.hh>

#define BRASIO_MESH_DISK_BASED_PYRAMID_DEFAULT_BASE_TESSELLATION 32
#define BRASIO_MESH_DISK_BASED_PYRAMID_DEFAULT_HEIGHT 1.0

namespace brasio::mesh
{

    class Cone : public Mesh
    {
    public:
        Cone(int base_tessellation =
                 BRASIO_MESH_DISK_BASED_PYRAMID_DEFAULT_BASE_TESSELLATION,
             float height = BRASIO_MESH_DISK_BASED_PYRAMID_DEFAULT_HEIGHT);

        static std::pair<std::vector<geometry::Vertex>, std::vector<uint16_t>>
        build(int base_tessellation, float height);
    };

} // namespace brasio::mesh

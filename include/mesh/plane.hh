#pragma once

#include <mesh/mesh.hh>

#define BRASIO_MESH_PLANE_DEFAULT_HORIZONTAL_TESSELLATION 10
#define BRASIO_MESH_PLANE_DEFAULT_VERTICAL_TESSELLATION 10

namespace brasio::mesh
{

    class Plane : public Mesh
    {
    public:
        Plane(int horizontal_tessellation =
                  BRASIO_MESH_PLANE_DEFAULT_HORIZONTAL_TESSELLATION,
              int vertical_tessellation =
                  BRASIO_MESH_PLANE_DEFAULT_VERTICAL_TESSELLATION);

        static std::pair<std::vector<geometry::Vertex>, std::vector<uint16_t>>
        build(int horizontal_tessellation, int vertical_tessellation);
    };
} // namespace brasio::mesh

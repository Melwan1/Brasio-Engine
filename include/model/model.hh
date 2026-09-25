#pragma once

#include <array>
#include <cstdint>
#include <map>
#include <tuple>
#include <vector>

#include <mesh/mesh.hh>
#include <io/files/obj-parser.hh>

namespace brasio::model
{
    using VertexType = std::array<float, 3>;
    using TextureCoordinatesType = std::array<float, 2>;
    using NormalType = std::array<float, 3>;
    using ParameterVertexType = std::array<float, 3>;
    using ElementIndexType = std::array<uint32_t, 3>;
    using FaceType = std::array<ElementIndexType, 3>;

    using VertexInfoType = std::tuple<VertexType, TextureCoordinatesType, NormalType>;
    using FaceIndicesType = std::array<uint32_t, 3>;

    class Model
    {
    public:
        Model();
        Model(io::files::OBJParser &objParser);

        mesh::MeshType toMesh();

    private:
        std::vector<VertexInfoType> _verticesInfo;
        std::vector<FaceIndicesType> _faceIndices;
    };
} // namespace brasio::model

#pragma once

#include <array>
#include <cstdint>
#include <memory>
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

    class Model;
    using ModelType = std::unique_ptr<Model>;

    class Model
    {
    public:
        Model(const std::string &id);
        Model(const std::string &id, io::files::OBJParser &objParser);

        const std::string &getId() const;

        mesh::MeshType toMesh();

        void upload(const renderer::vulkan::VulkanRenderer &renderer);
        mesh::Mesh &mesh();
        const mesh::Mesh &mesh() const;

        static ModelType unitQuad();

    private:
        const std::string _id;
        std::vector<VertexInfoType> _verticesInfo;
        std::vector<FaceIndicesType> _faceIndices;

        mesh::MeshType _mesh;
    };

    YAML::Emitter &operator<<(YAML::Emitter &out, const Model &model);

} // namespace brasio::model

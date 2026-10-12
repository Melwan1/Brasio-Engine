#include <model/model.hh>

#include <geometry/vertex.hh>

namespace brasio::model
{
    Model::Model()
    {
        _verticesInfo.clear();
        _faceIndices.clear();
    }

    Model::Model(io::files::OBJParser &objParser)
    {
        uint32_t vertexCount = objParser.getVertexCount();
        _verticesInfo.resize(vertexCount);
        std::vector<bool> filledVertices(vertexCount, false);
        uint32_t faceCount = objParser.getFaceCount();
        _faceIndices.reserve(faceCount);

        for (const auto &face : objParser.getFaces())
        {
            std::array<uint32_t, 3> indices;
            for (unsigned i = 0; i < 3; i++)
            {
                uint32_t vertexIndex = face[i][0] - 1;
                indices[i] = vertexIndex;
                if (!filledVertices[vertexIndex])
                {
                    filledVertices[vertexIndex] = true;
                    const auto &vertex = objParser.getVertices()[vertexIndex];

                    std::array<float, 3> defaultTexture = { 0.0f, 0.0f, 0.0f };
                    const auto &textureCoordinate = (face[i][1] > 0)
                        ? objParser.getTextureCoordinates()[face[i][1] - 1]
                        : defaultTexture;

                    std::array<float, 3> defaultNormal = { 0.0f, 0.0f,
                                                           0.0f }; // careful, norm is 0!!
                    const auto &normal =
                        (face[i][2] > 0) ? objParser.getNormals()[face[i][2] - 1] : defaultNormal;

                    _verticesInfo[vertexIndex] = { { vertex[0], vertex[1], vertex[2] },
                                                   { textureCoordinate[0], textureCoordinate[1] },
                                                   normal };
                }
            }
            _faceIndices.emplace_back(indices);
        }
    }

    mesh::MeshType Model::toMesh()
    {
        std::vector<geometry::Vertex> meshVertices;
        std::vector<mesh::Mesh::IndexType> meshIndices;

        for (const VertexInfoType &vertex : _verticesInfo)
        {
            geometry::Vertex shaderVertex;

            const VertexType &position = std::get<0>(vertex);
            shaderVertex.position = { position[0], position[1], position[2] };

            const TextureCoordinatesType &textureCoordinates = std::get<1>(vertex);
            shaderVertex.texCoord = { textureCoordinates[0], 1.0f - textureCoordinates[1] };

            const NormalType &normal = std::get<2>(vertex);
            shaderVertex.normal = { normal[0], normal[1], normal[2] };

            meshVertices.emplace_back(shaderVertex);
        }

        for (const FaceIndicesType &face : _faceIndices)
        {
            meshIndices.emplace_back(face[0]);
            meshIndices.emplace_back(face[1]);
            meshIndices.emplace_back(face[2]);
        }
        return std::make_unique<mesh::Mesh>(meshVertices, meshIndices);
    }

    void Model::upload(const renderer::vulkan::VulkanRenderer &renderer)
    {
        _mesh = toMesh();
        _mesh->createBuffers(renderer);
    }

    mesh::Mesh &Model::mesh()
    {
        return *_mesh;
    }

    const mesh::Mesh &Model::mesh() const
    {
        return *_mesh;
    }

    ModelType Model::unitQuad()
    {
        ModelType model = std::make_unique<Model>();
        model->_verticesInfo.reserve(4);
        model->_faceIndices.reserve(6);
        model->_faceIndices.insert(model->_faceIndices.begin(), { { 0, 1, 2 }, { 2, 3, 0 } });
        model->_verticesInfo.insert(
            model->_verticesInfo.begin(),
            { { { -0.5f, +0.5f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } },
              { { -0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f } },
              { { +0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f } },
              { { +0.5f, +0.5f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } } });
        return model;
    }
} // namespace brasio::model

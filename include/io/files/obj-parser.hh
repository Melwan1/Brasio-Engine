#pragma once

#include <array>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace brasio::io::files
{

    using VertexType = std::array<float, 4>;
    using TextureCoordinatesType = std::array<float, 3>;
    using NormalType = std::array<float, 3>;
    using ParameterVertexType = std::array<float, 3>;
    using ElementIndexType = std::array<uint32_t, 3>;
    using FaceType = std::vector<ElementIndexType>;

    class OBJParser
    {
    public:
        OBJParser(const fs::path &objPath);

        void load();
        void loadVertices();
        void loadTextureCoordinates();
        void loadNormals();
        void loadParameterVertices();
        void loadFaces();

        void dump(const fs::path &outputPath);

        const std::vector<VertexType> &getVertices() const;
        const std::vector<TextureCoordinatesType> &
        getTextureCoordinates() const;
        const std::vector<NormalType> &getNormals() const;
        const std::vector<ParameterVertexType> &getParameterVertices() const;
        const std::vector<FaceType> &getFaces() const;

        uint32_t getVertexCount() const;
        uint32_t getFaceCount() const;

    private:
        fs::path _objPath;
        std::ifstream _ifs;

        std::string _nextLine;

        std::vector<VertexType> _vertices;
        std::vector<TextureCoordinatesType> _textureCoordinates;
        std::vector<NormalType> _normals;
        std::vector<ParameterVertexType> _parameterVertices;
        std::vector<FaceType> _faces;

        void _getNextLine();
        void _skipIgnoredLines();
        bool _checkLineType(const std::string &start);

        uint32_t _parseIndex(std::istringstream &elementIndexStream);
        ElementIndexType
        _parseElementIndex(const std::string &elementIndexDefinition);
        FaceType _parseFace(const std::string &faceDefinition);
        void _error(const std::string &section, unsigned line, bool isIndex);
    };

} // namespace brasio::io::files

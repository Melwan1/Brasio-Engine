#include <io/files/obj-parser.hh>

#include <io/logging/logger.hh>

namespace brasio::io::files
{

    OBJParser::OBJParser(const fs::path &objPath)
        : _objPath(objPath)
        , _ifs(objPath)
        , _nextLine()
        , _vertices()
        , _textureCoordinates()
        , _normals()
        , _parameterVertices()
        , _faces()
    {}

    void OBJParser::load()
    {
        loadVertices();
        loadTextureCoordinates();
        loadNormals();
        loadParameterVertices();
        loadFaces();
    }

    void OBJParser::loadVertices()
    {
        while (_ifs.good())
        {
            _skipIgnoredLines();
            std::string start = "v ";
            if (!_checkLineType(start))
            {
                return;
            }
            std::string substr = _nextLine.substr(start.length());
            float x;
            float y;
            float z;
            float w = 1.0;
            std::istringstream iss(substr);
            if (!(iss >> x >> y >> z))
            {
                _error("vertices", _vertices.size() + 1, false);
            }
            iss >> w;
            _vertices.emplace_back(std::array{ x, y, z, w });
            _nextLine.clear();
        }
    }

    void OBJParser::loadTextureCoordinates()
    {
        while (_ifs.good())
        {
            _skipIgnoredLines();
            std::string start = "vt ";

            if (!_checkLineType(start))
            {
                return;
            }
            std::string substr = _nextLine.substr(start.length());
            float u;
            float v = 0.0;
            float w = 0.0;
            std::istringstream iss(substr);
            if (!(iss >> u))
            {
                _error("texture coordinates", _textureCoordinates.size() + 1, false);
            }
            iss >> v >> w;
            _textureCoordinates.emplace_back(std::array{ u, v, w });
            _nextLine.clear();
        }
    }

    void OBJParser::loadNormals()
    {
        while (_ifs.good())
        {
            _skipIgnoredLines();
            std::string start = "vn ";

            if (!_checkLineType(start))
            {
                return;
            }
            std::string substr = _nextLine.substr(start.length());
            float x;
            float y;
            float z;
            std::istringstream iss(substr);
            if (!(iss >> x >> y >> z))
            {
                _error("normals", _normals.size() + 1, false);
            }
            _normals.emplace_back(std::array{ x, y, z });
            _nextLine.clear();
        }
    }

    void OBJParser::loadParameterVertices()
    {
        while (_ifs.good())
        {
            _skipIgnoredLines();
            std::string start = "vp ";

            if (!_checkLineType(start))
            {
                return;
            }
            std::string substr = _nextLine.substr(start.length());
            float u;
            float v = 0.0;
            float w = 0.0;
            std::istringstream iss(substr);
            if (!(iss >> u))
            {
                _error("parameter vertices", _parameterVertices.size() + 1, false);
            }
            iss >> v >> w;
            _parameterVertices.emplace_back(std::array{ u, v, w });
            _nextLine.clear();
        }
    }

    void OBJParser::loadFaces()
    {
        while (_ifs.good())
        {
            _skipIgnoredLines();
            std::string start = "f ";

            if (!_checkLineType(start))
            {
                return;
            }
            std::string substr = _nextLine.substr(start.length());
            _faces.emplace_back(_parseFace(substr));
            _nextLine.clear();
        }
    }

    void OBJParser::dump(const fs::path &outputPath)
    {
        std::ofstream ofs(outputPath);
        for (const VertexType &vertex : _vertices)
        {
            ofs << "v " << vertex.at(0) << " " << vertex.at(1) << " " << vertex.at(2) << " " << vertex.at(3) << "\n";
        }
        for (const TextureCoordinatesType &textureCoordinates : _textureCoordinates)
        {
            ofs << "vt " << textureCoordinates.at(0) << " " << textureCoordinates.at(1) << " " << textureCoordinates.at(2) << "\n";
        }
        for (const NormalType &normal : _normals)
        {
            ofs << "vn " << normal.at(0) << " " << normal.at(1) << " " << normal.at(2) << "\n";
        }
        for (const ParameterVertexType &parameterVertex : _parameterVertices)
        {
            ofs << "vp " << parameterVertex.at(0) << " " << parameterVertex.at(1) << " " << parameterVertex.at(2) << "\n";
        }
        for (const FaceType &face : _faces)
        {
            ofs << "f";
            for (const ElementIndexType &elementIndex : face)
            {
                ofs << " " << elementIndex.at(0);
                if (elementIndex.at(1) && elementIndex.at(2))
                {
                    ofs << "/" << elementIndex.at(1) << "/" << elementIndex.at(2);
                }
                else if (elementIndex.at(1))
                {
                    ofs << "/" << elementIndex.at(1);
                }
                else if (elementIndex.at(2))
                {
                    ofs << "//" << elementIndex.at(2);
                }
            }
            ofs << "\n";
        }
    }

    const std::vector<VertexType> &OBJParser::getVertices() const
    {
        return _vertices;
    }

    const std::vector<TextureCoordinatesType> &OBJParser::getTextureCoordinates() const
    {
        return _textureCoordinates;
    }

    const std::vector<NormalType> &OBJParser::getNormals() const
    {
        return _normals;
    }

    const std::vector<ParameterVertexType> &OBJParser::getParameterVertices() const
    {
        return _parameterVertices;
    }

    const std::vector<FaceType> &OBJParser::getFaces() const
    {
        return _faces;
    }

    uint32_t OBJParser::getVertexCount() const
    {
        return _vertices.size();
    }

    uint32_t OBJParser::getFaceCount() const
    {
        return _faces.size();
    }

    void OBJParser::_skipIgnoredLines()
    {
        if (_ifs.good() && !_ifs.eof() && _nextLine.empty())
        {
            _getNextLine();
        }
        while (_ifs.good() && (_nextLine.empty() || _nextLine.starts_with("#") || _nextLine.starts_with("o") || _nextLine.starts_with("g") || _nextLine.starts_with("mtllib") || _nextLine.starts_with("usemtl") || _nextLine.starts_with("s")))
        {
            _getNextLine();
        }
    }

    void OBJParser::_getNextLine()
    {
        std::getline(_ifs, _nextLine);
    }

    bool OBJParser::_checkLineType(const std::string &start)
    {
        return _nextLine.starts_with(start);
    }

    FaceType OBJParser::_parseFace(const std::string &faceDefinition)
    {
        FaceType face;
        std::istringstream faceStream(faceDefinition);
        std::string elementIndexDefinition;
        while (std::getline(faceStream, elementIndexDefinition, ' '))
        {
            face.emplace_back(_parseElementIndex(elementIndexDefinition));
        }
        return face;
    }

    uint32_t OBJParser::_parseIndex(std::istringstream &elementIndexStream)
    {
        uint32_t index = 0;
        if (!(elementIndexStream >> index))
        {
            _error("faces", _faces.size() + 1, true);
        }
        return index;
    }

    ElementIndexType OBJParser::_parseElementIndex(const std::string &elementIndexDefinition)
    {
        std::istringstream elementIndexStream(elementIndexDefinition);
        uint32_t vertexIndex = _parseIndex(elementIndexStream);
        if (elementIndexStream.eof())
        {
            return { vertexIndex, 0, 0 };
        }
        elementIndexStream.ignore(1);

        if (elementIndexStream.peek() == '/')
        {
            elementIndexStream.ignore(1);
            uint32_t normalIndex = _parseIndex(elementIndexStream);
            return { vertexIndex, 0, normalIndex };
        }
        uint32_t textureIndex = _parseIndex(elementIndexStream);
        if (elementIndexStream.eof())
        {
            return { vertexIndex, textureIndex, 0 };
        }
        elementIndexStream.ignore(1);
        uint32_t normalIndex = _parseIndex(elementIndexStream);
        if (!elementIndexStream.eof())
        {
            BRASIO_LOG_ERROR("OBJ file (" + _objPath.string() + ") at faces section, line " + std::to_string(_faces.size() + 1) + " is ill-formatted.", { "IO", "FILES" });
        }
        return { vertexIndex, textureIndex, normalIndex };

    }

    void OBJParser::_error(const std::string &section, unsigned line, bool isIndex)
    {
        std::ostringstream oss;
        oss << "OBJ file (" << _objPath.string() << ") at " << section << " section, line " << line << " is lacking mandatory " << (isIndex ? "indices" : "coordinates");
        BRASIO_LOG_ERROR(oss.str(), { "IO", "FILES" });
    }
}

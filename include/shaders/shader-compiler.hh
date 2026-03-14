#pragma once

#include <filesystem>

namespace brasio::shaders
{
    namespace fs = std::filesystem;

    class ShaderCompiler
    {
    public:
        ShaderCompiler(const fs::path &baseShaderDirectoryPath,
                       const fs::path &logPath);

        bool compileShader(const fs::path &shaderPath) const;
        std::pair<const fs::path, const fs::path>
        getEntryPaths(const fs::path &entry) const;

    private:
        fs::path _baseShaderDirectoryPath;
        fs::path _logPath;
    };
} // namespace brasio::shaders

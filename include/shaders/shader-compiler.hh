#pragma once

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

class ShaderCompiler
{
public:
    ShaderCompiler(const fs::path &baseShaderDirectoryPath, const fs::path &logPath);

    bool compileShader(const fs::path &shaderPath);
    std::pair<const fs::path, const fs::path> getEntryPaths(const fs::path &entry);

private:
    fs::path _baseShaderDirectoryPath;
    fs::path _logPath;

};
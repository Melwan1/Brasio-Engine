#pragma once

#include <filesystem>
#include <map>

#include <shaders/shader-compiler.hh>

#include <vulkan/vulkan.hpp>

namespace fs = std::filesystem;

class ShaderManager
{
public:
    ShaderManager(const fs::path &baseShaderDirectoryPath,
                  const fs::path &logPath);
    ~ShaderManager();

    bool compileAllShaders();
    void readSpirVFile(const fs::path &outputPath);

    const std::string &getSpirVFileContent(const fs::path &entry);

    VkShaderModule
    createShaderModuleFromByteCode(VkDevice &device,
                                   const std::string &shaderByteCode);
    VkShaderModule createShaderModuleFromPath(VkDevice &device,
                                              const fs::path &entry);

private:
    ShaderCompiler _shaderCompiler;
    std::map<const fs::path, const std::string> _shaderLocationToContent{};
    const fs::path _baseShaderDirectoryPath;
    const fs::path _logPath;
};

#include <shaders/shader-manager.hh>

#include <fstream>
#include <iostream>

ShaderManager::ShaderManager(const fs::path &baseShaderDirectoryPath,
                             const fs::path &logPath)
    : _shaderCompiler(baseShaderDirectoryPath, logPath)
    , _shaderLocationToContent()
    , _baseShaderDirectoryPath(baseShaderDirectoryPath)
    , _logPath(logPath)
{}

bool ShaderManager::compileAllShaders()
{
    const fs::path destDirectoryPath("compiled-shaders/");
    for (const auto &entry :
         fs::recursive_directory_iterator(_baseShaderDirectoryPath))
    {
        if (!entry.is_regular_file())
        {
            continue;
        }
        if (!_shaderCompiler.compileShader(
                fs::relative(entry, _baseShaderDirectoryPath)))
        {
            return false;
        }
        auto outputEntry = _shaderCompiler.getEntryPaths(entry);
        readSpirVFile(outputEntry.second);
    }
    return true;
}

void ShaderManager::readSpirVFile(const fs::path &outputPath)
{
    std::ifstream ifs(outputPath.string(), std::ios::ate | std::ios::binary);
    size_t fileSize = ifs.tellg();
    ifs.seekg(0);
    std::string fileContent(fileSize, 0);
    ifs.read(fileContent.data(), fileSize);
    _shaderLocationToContent.insert({ outputPath.string(), fileContent });
}

const std::string &ShaderManager::getSpirVFileContent(const fs::path &entry)
{
    return _shaderLocationToContent.at(
        _shaderCompiler.getEntryPaths(entry).second);
}

VkShaderModule
ShaderManager::createShaderModuleFromByteCode(VkDevice &device,
                                              const std::string &shaderByteCode)
{
    // the shaderByteCode string is cast to a uint32_t, so it needs to be
    // realloced in order to be aligned on 4 bytes.
    size_t alignment = 4;
    size_t paddingToAdd =
        (alignment - shaderByteCode.size() % alignment) % alignment;
    const std::string finalShaderByteCode =
        shaderByteCode + std::string(paddingToAdd, 0);
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = finalShaderByteCode.length();
    createInfo.pCode =
        reinterpret_cast<const uint32_t *>(finalShaderByteCode.data());

    VkShaderModule shaderModule;
    if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule)
        != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create shader module.");
    }
    return shaderModule;
}

VkShaderModule ShaderManager::createShaderModuleFromPath(VkDevice &device,
                                                         const fs::path &entry)
{
    return createShaderModuleFromByteCode(device, getSpirVFileContent(entry));
}

ShaderManager::~ShaderManager()
{
    fs::remove("output.log");
}

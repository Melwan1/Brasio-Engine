#include <shaders/shader-manager.hh>

#include <fstream>
#include <iostream>

ShaderManager::ShaderManager(const fs::path &baseShaderDirectoryPath, const fs::path &logPath)
    : _shaderCompiler(baseShaderDirectoryPath, logPath)
    , _shaderLocationToContent()
    , _baseShaderDirectoryPath(baseShaderDirectoryPath)
    , _logPath(logPath)
{}

bool ShaderManager::compileAllShaders()
{
    const fs::path destDirectoryPath("compiled-shaders/");
    for (const auto &entry : fs::recursive_directory_iterator(_baseShaderDirectoryPath))
    {
        if (!entry.is_regular_file())
        {
            continue;
        }
        std::cout << "entry: " << entry << "\n";
        if (!_shaderCompiler.compileShader(fs::relative(entry, _baseShaderDirectoryPath)))
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
    _shaderLocationToContent.insert({outputPath.string(), fileContent});
}

const std::string &ShaderManager::getSpirVFileContent(const fs::path &entry)
{
    return _shaderLocationToContent.at(_shaderCompiler.getEntryPaths(entry).second);
}

ShaderManager::~ShaderManager()
{
    fs::remove_all("compiled-shaders/");
    fs::remove("output.log");
}
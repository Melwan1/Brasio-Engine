#include <shaders/shader-compiler.hh>

#include <fstream>
#include <iostream>

ShaderCompiler::ShaderCompiler(const fs::path &baseShaderDirectoryPath, const fs::path &logPath)
    : _baseShaderDirectoryPath(baseShaderDirectoryPath)
    , _logPath(logPath)
{}

std::pair<const fs::path, const fs::path> ShaderCompiler::getEntryPaths(const fs::path &entry)
{
    const fs::path destDirectoryPath("compiled-shaders/");
    const fs::path destPath = (destDirectoryPath / fs::relative(entry, _baseShaderDirectoryPath)).replace_extension(".spv");
    return { entry, destPath };
}

bool ShaderCompiler::compileShader(const fs::path &shaderPath)
{
    const fs::path destDirectoryPath("compiled-shaders/");
    const fs::path resolvedPath = _baseShaderDirectoryPath / shaderPath;
    const fs::path destPath = (destDirectoryPath / fs::relative(resolvedPath, _baseShaderDirectoryPath)).replace_extension(".spv");
    fs::create_directories(destPath.parent_path());

    std::ostringstream commandStream;
    commandStream << "glslc " << resolvedPath << " -o " << destPath << " 2>" << _logPath;
    int returnCode = system(commandStream.str().c_str());
    if (!returnCode)
    {
        return true;
    }
    // compilation failed
    std::ifstream ifs(_logPath, std::ios::ate);
    size_t fileSize = ifs.tellg();
    std::string fileContent(fileSize, 0);
    ifs.seekg(0);
    ifs.read(fileContent.data(), fileSize);

    std::cerr << "Compilation failed for shader " << shaderPath << "(return code " << returnCode << "):\n" << fileContent;
    return false;
}
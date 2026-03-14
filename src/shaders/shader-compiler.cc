#include <filesystem>
#include <shaders/shader-compiler.hh>
#include <io/logging/logger.hh>
#include <io/files/stat-utils.hh>

#include <fstream>
#include <iostream>

namespace brasio::shaders
{
    ShaderCompiler::ShaderCompiler(const fs::path &baseShaderDirectoryPath,
                                   const fs::path &logPath)
        : _baseShaderDirectoryPath(baseShaderDirectoryPath)
        , _logPath(logPath)
    {}

    std::pair<const fs::path, const fs::path>
    ShaderCompiler::getEntryPaths(const fs::path &entry) const
    {
        const fs::path destDirectoryPath("compiled-shaders/");
        const fs::path destPath =
            (destDirectoryPath
             / entry) // fs::relative(entry, _baseShaderDirectoryPath))
                .replace_extension(".spv");
        return { entry, destPath };
    }

    bool ShaderCompiler::compileShader(const fs::path &shaderPath) const
    {
        io::logging::Logger::debug(std::cout,
                                   "Compiling shader: " + shaderPath.string(),
                                   { "SHADERS" });
        const fs::path destDirectoryPath("compiled-shaders/");
        const fs::path resolvedPath = _baseShaderDirectoryPath / shaderPath;
        const fs::path destPath =
            (destDirectoryPath
             / fs::relative(resolvedPath, _baseShaderDirectoryPath))
                .replace_extension(".spv");
        fs::create_directories(destPath.parent_path());

        io::logging::Logger::trace(
            std::cout,
            "Shader " + resolvedPath.string() + " write time: "
                + io::files::StatUtils::writeTimeToString(resolvedPath),
            { "SHADERS" });
        io::logging::Logger::trace(
            std::cout,
            "Compiled shader " + destPath.string() + " write time: "
                + io::files::StatUtils::writeTimeToString(destPath),
            { "SHADERS" });

        if (fs::exists(destPath)
            && fs::last_write_time(destPath)
                >= fs::last_write_time(resolvedPath))
        {
            io::logging::Logger::info(
                std::cout,
                "Shader " + resolvedPath.string()
                    + " does not need to be compiled again.",
                { "SHADERS" });
            return true;
        }

        std::ostringstream commandStream;
        commandStream << "glslc " << resolvedPath << " -o " << destPath << " 2>"
                      << _logPath;
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

        std::ostringstream err;
        err << "Shader " << shaderPath.string() << ": compilation failed.";
        io::logging::Logger::error(std::cout, err.str(), { "SHADERS" });
        err.clear();
        err << "Return code: " << returnCode;
        io::logging::Logger::error(std::cout, err.str(), { "SHADERS" });
        err.clear();
        err << "Error: " << fileContent;
        io::logging::Logger::error(std::cout, err.str(), { "SHADERS" });
        return false;
    }
} // namespace brasio::shaders

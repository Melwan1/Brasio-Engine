#include <utils/version.hh>

#include <io/logging/logger.hh>

namespace brasio::utils
{

    Version::Version(const std::string &versionStr)
    {
        size_t firstDotPosition = versionStr.find(".");
        if (firstDotPosition == std::string::npos)
        {
            fail();
        }
        size_t secondDotPosition = versionStr.find(".", firstDotPosition + 1);
        if (secondDotPosition == std::string::npos)
        {
            fail();
        }
        std::istringstream majorStream(versionStr.substr(
            (versionStr[0] == 'v') ? 1 : 0, firstDotPosition));
        std::istringstream minorStream(versionStr.substr(
            firstDotPosition + 1, secondDotPosition - firstDotPosition - 1));
        std::istringstream patchStream(
            versionStr.substr(secondDotPosition + 1));

        int major = -1;
        int minor = -1;
        int patch = -1;
        if (!((majorStream >> major) && (minorStream >> minor)
              && (patchStream >> patch)))
        {
            fail();
        }
        setVersion(major, minor, patch);
    }

    Version::Version(int major, int minor, int patch)
        : _major(major)
        , _minor(minor)
        , _patch(patch)
    {}

    void Version::setVersion(int major, int minor, int patch)
    {
        if (major < 0 || minor < 0 || patch < 0)
        {
            fail();
        }
        _major = major;
        _minor = minor;
        _patch = patch;
    }

    void Version::fail()
    {
        _major = 0;
        _minor = 0;
        _patch = 0;
        io::logging::Logger::warning(
            std::cout,
            "Could not set version from string, setting version to 0.0.0",
            { "VERSION" });
    }

    int Version::getMajor() const
    {
        return _major;
    }

    int Version::getMinor() const
    {
        return _minor;
    }

    int Version::getPatch() const
    {
        return _patch;
    }

    std::string Version::toString() const
    {
        std::ostringstream oss;
        oss << getMajor() << "." << getMinor() << "." << getPatch();
        return oss.str();
    }

} // namespace brasio::utils

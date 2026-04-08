#pragma once

#include <string>

namespace brasio::utils
{

    class Version
    {
    public:
        Version(const std::string &versionStr);
        Version(int major = 0, int minor = 0, int patch = 0);

        void setVersion(int major, int minor, int patch);

        void fail();

        int getMajor() const;
        int getMinor() const;
        int getPatch() const;

        std::string toString() const;

    private:
        int _major;
        int _minor;
        int _patch;
    };

} // namespace brasio::utils

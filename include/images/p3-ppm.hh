#pragma once

#include <array>
#include <filesystem>
#include <ostream>
#include <vector>

namespace fs = std::filesystem;

namespace brasio::images
{

    class P3PPM
    {
    public:
        using PixelType = std::array<unsigned char, 3>;
        using PixelArray = std::vector<PixelType>;

        P3PPM(unsigned width, unsigned height, const PixelArray &pixels);

        static P3PPM load(const fs::path &path);

        void print(std::ostream &ostr);

    private:
        unsigned _width;
        unsigned _height;
        PixelArray _pixels;
    };
} // namespace brasio::images

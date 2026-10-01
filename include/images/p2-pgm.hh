#pragma once

#include <filesystem>
#include <ostream>
#include <vector>

namespace fs = std::filesystem;

namespace brasio::images
{

    class P2PGM
    {
    public:
        using PixelType = unsigned char;
        using PixelArray = std::vector<PixelType>;

        P2PGM(unsigned width, unsigned height, const PixelArray &pixels);

        static P2PGM load(const fs::path &path);
        static P2PGM empty();

        void print(std::ostream &ostr);
        void save(const fs::path &path);

        size_t getSize() const;
        size_t getWidth() const;
        size_t getHeight() const;
        const void *getData() const;
        void *getData();

    private:
        unsigned _width;
        unsigned _height;
        PixelArray _pixels;
    };
} // namespace brasio::images

#include <images/p2-pgm.hh>

#include <io/logging/logger.hh>
#include <utils/libutils.hh>

#include <fstream>
#include <sstream>

namespace brasio::images
{

    P2PGM::P2PGM(unsigned width, unsigned height, const PixelArray &pixels)
        : _width(width)
        , _height(height)
        , _pixels(pixels)
    {}

    P2PGM P2PGM::load(const fs::path &path)
    {
        std::ifstream ifs(path);
        std::string format;
        if (!(std::getline(ifs, format)))
        {
            BRASIO_LOG_WARNING("Unknown PPM format, assuming P2.", { "IMAGES", "PPM", "LOAD" });
            format = "P2";
        }
        unsigned width, height, maxValue;
        if (!(ifs >> width >> height >> maxValue))
        {
            BRASIO_LOG_ERROR("Could not parse width, height or max value from "
                             "the P2 PGM file, aborting.",
                             { "IMAGES", "PPM", "LOAD" });
        }
        // there should be no overflow here, it's not possible to
        // read a 12 or 24 GB image file anyway...
        unsigned numPixels = width * height;
        PixelArray pixels;
        pixels.resize(numPixels);
        if (maxValue != 255)
        {
            BRASIO_LOG_WARNING("maxValue is not 255, multiplying every value "
                               "by 255 / maxValue to put max value at 255",
                               { "IMAGES", "PPM", "LOAD" });
        }
        unsigned index = 0;
        for (unsigned line = 0; line < height; line++)
        {
            for (unsigned col = 0; col < width; col++)
            {
                unsigned value;
                if (!(ifs >> value))
                {
                    std::ostringstream oss;
                    oss << "Could not read pixel at coordinates (" << line << ", " << col
                        << "), the image result might be corrupted";
                    BRASIO_LOG_ERROR(oss.str(), { "IMAGES", "PPM", "LOAD" });
                }

                pixels[index++] = utils::pixel_to_unsigned_char(value, maxValue);
            }
        }
        unsigned thrownUnsigned;
        if (ifs >> thrownUnsigned)
        {
            BRASIO_LOG_ERROR("Image file is longer than " + std::to_string(numPixels) + " pixels",
                             { "IMAGES", "PPM", "LOAD" });
        }
        return { width, height, pixels };
    }

    P2PGM P2PGM::empty()
    {
        return { 1, 1, { 0 } };
    }

    void P2PGM::print(std::ostream &ostr)
    {
        ostr << "P2\n" << _width << " " << _height << "\n" << 255 << "\n";
        unsigned cur_width = 0;
        for (const PixelType &pixel : _pixels)
        {
            ostr << static_cast<unsigned>(pixel);
            if (cur_width++ == _width - 1)
            {
                ostr << "\n";
                cur_width = 0;
            }
            else
            {
                ostr << " ";
            }
        }
    }

    void P2PGM::save(const fs::path &path)
    {
        std::ofstream ostr(path);
        print(ostr);
    }

    size_t P2PGM::getSize() const
    {
        return _width * _height;
    }

    size_t P2PGM::getWidth() const
    {
        return _width;
    }

    size_t P2PGM::getHeight() const
    {
        return _height;
    }

    const void *P2PGM::getData() const
    {
        return _pixels.data();
    }

    void *P2PGM::getData()
    {
        return _pixels.data();
    }

    P2PGM::PixelType P2PGM::operator[](unsigned index) const
    {
        return _pixels[index];
    }

} // namespace brasio::images

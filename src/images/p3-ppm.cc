#include <images/p3-ppm.hh>

#include <fstream>
#include <sstream>
#include <io/logging/logger.hh>
#include <utils/libutils.hh>
#include "utils/image-conversions.hh"

namespace brasio::images
{

    P3PPM::P3PPM(unsigned width, unsigned height, const PixelArray &pixels)
        : _width(width)
        , _height(height)
        , _pixels(pixels)
    {}

    P3PPM P3PPM::load(const fs::path &path)
    {
        std::ifstream ifs(path);
        std::string format;
        if (!(std::getline(ifs, format)))
        {
            BRASIO_LOG_WARNING("Unknown PPM format, assuming P3.", { "IMAGES", "PPM", "LOAD" });
            format = "P3";
        }
        unsigned width, height, maxValue;
        if (!(ifs >> width >> height >> maxValue))
        {
            BRASIO_LOG_ERROR("Could not parse width, height or max value from "
                             "the P3 PPM file, aborting.",
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
                unsigned red, green, blue;
                if (!(ifs >> red >> green >> blue))
                {
                    std::ostringstream oss;
                    oss << "Could not read pixel at coordinates (" << line << ", " << col
                        << "), the image result might be corrupted";
                    BRASIO_LOG_ERROR(oss.str(), { "IMAGES", "PPM", "LOAD" });
                }

                pixels[index++] = { utils::pixel_to_unsigned_char(red, maxValue),
                                    utils::pixel_to_unsigned_char(green, maxValue),
                                    utils::pixel_to_unsigned_char(blue, maxValue), 255 };
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

    P3PPM P3PPM::empty()
    {
        return { 1, 1, { { 0, 0, 0 } } };
    }

    void P3PPM::print(std::ostream &ostr)
    {
        ostr << "P3\n" << _width << " " << _height << "\n" << 255 << "\n";
        unsigned curWidth = 0;
        for (const PixelType &pixel : _pixels)
        {
            ostr << static_cast<unsigned>(pixel.at(0)) << " " << static_cast<unsigned>(pixel.at(1))
                 << " " << static_cast<unsigned>(pixel.at(2));
            if (curWidth++ == _width - 1)
            {
                ostr << "\n";
                curWidth = 0;
            }
            else
            {
                ostr << " ";
            }
        }
    }

    void P3PPM::save(const fs::path &path)
    {
        std::ofstream ostr(path);
        print(ostr);
    }

    size_t P3PPM::getSize() const
    {
        return _width * _height * 4;
    }

    size_t P3PPM::getWidth() const
    {
        return _width;
    }

    size_t P3PPM::getHeight() const
    {
        return _height;
    }

    const void *P3PPM::getData() const
    {
        return _pixels.data()->data();
    }

    void *P3PPM::getData()
    {
        return _pixels.data()->data();
    }

    const P3PPM::PixelType &P3PPM::operator[](unsigned index) const
    {
        return _pixels[index];
    }

} // namespace brasio::images

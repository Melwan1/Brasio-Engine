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
            BRASIO_LOG_WARNING(std::cout, "Unknown PPM format, assuming P3.",
                               { "IMAGES", "PPM", "LOAD" });
            format = "P3";
        }
        unsigned width, height, max_value;
        if (!(ifs >> width >> height >> max_value))
        {
            BRASIO_LOG_ERROR(std::cout,
                             "Could not parse width, height or max value from "
                             "the P3 PPM file, aborting.",
                             { "IMAGES", "PPM", "LOAD" });
        }
        // there should be no overflow here, it's not possible to
        // read a 12 or 24 GB image file anyway...
        unsigned num_pixels = width * height;
        PixelArray pixels;
        pixels.resize(num_pixels);
        if (max_value != 255)
        {
            BRASIO_LOG_WARNING(std::cout,
                               "max_value is not 255, multiplying every value "
                               "by 255 / max_value to put max value at 255",
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
                    oss << "Could not read pixel at coordinates (" << line
                        << ", " << col
                        << "), the image result might be corrupted";
                    BRASIO_LOG_ERROR(std::cout, oss.str(),
                                     { "IMAGES", "PPM", "LOAD" });
                }

                pixels[index++] = {
                    utils::pixel_to_unsigned_char(red, max_value),
                    utils::pixel_to_unsigned_char(green, max_value),
                    utils::pixel_to_unsigned_char(blue, max_value)
                };
            }
        }
        unsigned thrown_unsigned;
        if (ifs >> thrown_unsigned)
        {
            BRASIO_LOG_ERROR(std::cout,
                             "Image file is longer than "
                                 + std::to_string(num_pixels) + " pixels",
                             { "IMAGES", "PPM", "LOAD" });
        }
        return { width, height, pixels };
    }

    void P3PPM::print(std::ostream &ostr)
    {
        ostr << "P3\n" << _width << " " << _height << "\n" << 255 << "\n";
        unsigned cur_width = 0;
        for (const PixelType &pixel : _pixels)
        {
            ostr << static_cast<unsigned>(pixel.at(0)) << " "
                 << static_cast<unsigned>(pixel.at(1)) << " "
                 << static_cast<unsigned>(pixel.at(2));
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

} // namespace brasio::images

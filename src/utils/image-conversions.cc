#include <utils/image-conversions.hh>

namespace brasio::utils
{

    unsigned char pixel_to_unsigned_char(float value, float max_value)
    {
        return static_cast<unsigned char>(value * max_value / 255);
    }

} // namespace brasio::utils

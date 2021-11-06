#include "src/videolib/utils/coordinate_helper.hpp"

ml::Vector<int, 2> vl::CoordinateHelper::toPixels(ml::Vector<int, 2> window, ml::Vector<float, 2> normalized)
{
    auto windowCenter { 0.5f * static_cast<ml::Vector<float, 2>>(window) };
    int pixelX = windowCenter[0] + 0.5f * (normalized[0] * window[0]);
    int pixelY = windowCenter[1] - 0.5f * (normalized[1] * window[1]);

    return { pixelX, pixelY };
}

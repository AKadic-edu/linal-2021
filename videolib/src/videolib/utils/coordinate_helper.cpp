#include "src/videolib/utils/coordinate_helper.hpp"

ml::Vector<int, 2> vl::CoordinateHelper::toPixels(ml::Vector<int, 2> viewport, ml::Vector<float, 2> relative)
{
    auto center = 0.5f * static_cast<ml::Vector<float, 2>>(viewport);
    int pixelX = center[0] + 0.5f * (relative[0] * viewport[0]);
    int pixelY = center[1] - 0.5f * (relative[1] * viewport[1]);

    return { pixelX, pixelY };
}

ml::Vector<float, 2> vl::CoordinateHelper::toRelative(ml::Vector<int, 2> viewport, ml::Vector<int, 2> pixels)
{
    auto center = 0.5f * static_cast<ml::Vector<float, 2>>(viewport);
    auto p = static_cast<ml::Vector<float, 2>>(pixels);
    float relativeX =  pixels[0] / center[0] - 1;
    float relativeY = -pixels[1] / center[1] + 1;

    return { relativeX, relativeY };
}

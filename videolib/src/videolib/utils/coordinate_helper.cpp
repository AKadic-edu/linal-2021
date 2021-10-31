#include "src/videolib/utils/coordinate_helper.hpp"

ml::Vector<int, 2> vl::CoordinateHelper::toPixels(ml::Vector<int, 2> window, ml::Vector<float, 2> normalized)
{
    auto windowCenter { 0.5f * window };
    int normalizedX = windowCenter[0] + 0.5f * (normalized[0] * window[0]);
    int normalizedY = windowCenter[1] - 0.5f * (normalized[1] * window[1]);

    return { normalizedX, normalizedY };
}

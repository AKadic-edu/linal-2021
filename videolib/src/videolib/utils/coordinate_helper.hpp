#pragma once

#ifndef VIDEOLIB_UTILS_COORDINATE_HELPER_HPP
#define VIDEOLIB_UTILS_COORDINATE_HELPER_HPP

#include <mathlib/vector.hpp>

namespace vl {
    class CoordinateHelper {
    public:
        static ml::Vector<int, 2> toPixels(ml::Vector<int, 2>, ml::Vector<float, 2>);
    };
}

#endif // !VIDEOLIB_UTILS_COORDINATE_HELPER_HPP

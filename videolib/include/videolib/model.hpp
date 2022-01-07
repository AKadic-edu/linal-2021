#pragma once

#ifndef VIDEOLIB_MODEL_HPP
#define VIDEOLIB_MODEL_HPP

#include <vector>

#include <mathlib/matrix.hpp>
#include <mathlib/utils/operations.hpp>

namespace vl {
	struct Model {
		ml::Matrix<float, 4, 4> worldM{ ml::identity<float, 4, 4>() };
		ml::Matrix<float, 4, 4> modelM{ ml::identity<float, 4, 4>() };
		std::vector<ml::Vector<float, 3>> vertices;

		static Model create(std::vector<float>);
	};
}

#endif // !VIDEOLIB_MODEL_HPP

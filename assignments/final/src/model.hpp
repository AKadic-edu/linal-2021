#pragma once

#ifndef MODEL_HPP
#define MODEL_HPP

#include "final.hpp"

struct Model {
	ml::Matrix<float, 3, 3> modelM { ml::identity<float, 3, 3>() };
	std::vector<ml::Vector<float, 2>> vertices;
};

#endif // !MODEL_HPP

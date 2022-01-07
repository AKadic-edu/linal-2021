#include "include/videolib/model.hpp"

vl::Model vl::Model::create(std::vector<float> v)
{
	Model m;

	for (int i = 0; i < v.size(); i += 3) {
		m.vertices.push_back({ v[i], v[i + 1], v[i + 2] });
	}

	return m;
}

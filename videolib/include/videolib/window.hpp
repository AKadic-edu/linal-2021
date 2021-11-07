#pragma once

#ifndef VIDEOLIB_WINDOW_HPP
#define VIDEOLIB_WINDOW_HPP

#include <functional>
#include <memory>
#include <string>

namespace vl {
	struct Window {
		std::string title;
		int width;
		int height;
	};
}

#endif // !VIDEOLIB_WINDOW_HPP

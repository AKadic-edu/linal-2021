#include <mathlib/matrix.hpp>
#include <mathlib/vector.hpp>
#include <mathlib/utils/operations.hpp>

#include "mathlib.hpp"

TEST_CASE("Matrix operations") {
	SECTION("transpose") {
		// Arrange
		ml::Matrix<float, 3, 2> expected { ml::Vector<float, 3>
			{ 1.0f, 3.0f, 5.0f },
			{ 2.0f, 4.0f, 6.0f },
		};
		ml::Matrix<float, 2, 3> m { ml::Vector<float, 2>
			{ 1.0f, 2.0f },
			{ 3.0f, 4.0f },
			{ 5.0f, 6.0f }
		};

		// Act
		auto result = ml::transpose(m);

		// Assert
		REQUIRE(result == expected);
	}
}

TEST_CASE("Vector operations") {
	SECTION("dot") {
		// Arrange
		float expected = 2.0f * 8.0f + 7.0f * 2.0f + 1.0f * 8.0f;
		ml::Vector<float, 3> a { 2.0f, 7.0f, 1.0f };
		ml::Vector<float, 3> b { 8.0f, 2.0f, 8.0f };

		// Act
		auto result = ml::dot(a, b);

		// Assert
		REQUIRE(result == expected);
	}
}

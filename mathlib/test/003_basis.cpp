#include <mathlib/matrix.hpp>
#include <mathlib/vector.hpp>

#include "mathlib.hpp"

TEST_CASE("Basis") {
	SECTION("multiplication") {
		SECTION("by vector") {
			// Arrange
			float a = 5.0f;
			float b = 2.0f;
			ml::Vector<float, 2> i { 1.0f, 0.0f };
			ml::Vector<float, 2> j { 0.0f, 1.0f };
			ml::Vector<float, 2> expected { a, b };

			// Act
			ml::Vector<float, 2> c { a * i + b * j };

			// Assert
			REQUIRE(c == expected);
		}
		SECTION("by matrix") {
			// Arrange
			ml::Matrix<float, 2, 2> m;
			m[0] = {  0.0f, 1.0f };
			m[1] = { -1.0f, 0.0f };
			ml::Vector<float, 2> v { 1.0f, 2.0f };
			ml::Vector<float, 2> expected { -2.0f, 1.0f };

			// Act
			auto mv = m * v;

			// Assert
			REQUIRE(mv == expected);
		}
	}
}

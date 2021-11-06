#include <mathlib/vector.hpp>

#include "mathlib.hpp"

TEST_CASE("Vector") {
	SECTION("addition") {
		SECTION("by vector") {
			// Arrange
			// Act
			// Assert
			REQUIRE(true);
		}
	}
	SECTION("subtraction") {
		SECTION("by vector") {
			// Arrange
			// Act
			// Assert
			REQUIRE(true);
		}
	}
	SECTION("multiplication") {
		SECTION("by scalar") {
			// Arrange
			float a = -1.0f;
			float b = 2.0f;
			ml::Vector<float, 2> i { 1.0f, -2.0f };
			ml::Vector<float, 2> j { 3.0f, 0.0f };
			ml::Vector<float, 2> expected { 5, 2 };

			// Act
			ml::Vector<float, 2> c { a * i + b * j };

			// Assert
			REQUIRE(c == expected);
		}
		SECTION("by vector") {
			REQUIRE(true);
		}
	}
}

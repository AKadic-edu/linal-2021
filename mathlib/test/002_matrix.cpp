#include <mathlib/matrix.hpp>

#include "mathlib.hpp"

TEST_CASE("Matrix") {
	SECTION("multiplication") {
		SECTION("by vector") {
			// Arrange
			ml::Matrix<float, 2, 2> m;
			m[0] = { 1.0f, -2.0f };
			m[1] = { 3.0f,  0.0f };
			ml::Vector<float, 2> v { -1.0f, 2.0f };
			ml::Vector<float, 2> expected { 5.0f, 2.0f };

			// Act
			auto mv = m * v;

			// Assert
			REQUIRE(mv == expected);
		}
		SECTION("by vector") {
			// Arrange
			ml::Matrix<float, 2, 2> m;
			m[0] = { 3.0f, -2.0f };
			m[1] = { 2.0f,  1.0f };
			ml::Vector<float, 2> v { 5.0f, 7.0f };
			ml::Vector<float, 2> expected { 29.0f, -3.0f };

			// Act
			auto mv = m * v;

			// Assert
			REQUIRE(mv == expected);
		}
		SECTION("by matrix") {
			// Arrange
			// Act
			// Assert
			REQUIRE(true);
		}
	}
}

#include <mathlib/matrix.hpp>

#include "mathlib.hpp"

TEST_CASE("2x1 matrix") {
	SECTION("can be multiplied") {
		SECTION("by vector") {
			// Arrange
			ml::Vector<float, 2> v { 4.0f, 3.0f };
			ml::Matrix<float, 1, 2> m { ml::Vector<float, 1>
				{  1.0f },
				{ -2.0f }
			};
			float expected = 4.0f * 1.0f + 3.0f * -2.0f;

			// Act
			auto mv = m * v;

			// Assert
			REQUIRE(mv == expected);
		}
	}
}

TEST_CASE("2x2 matrix") {
	SECTION("can be multiplied") {
		SECTION("by vector") {
			// Arrange
			ml::Matrix<float, 2, 2> m { ml::Vector<float, 2>
				{ 1.0f, -2.0f },
				{ 3.0f,  0.0f }
			};
			ml::Vector<float, 2> v { -1.0f, 2.0f };
			ml::Vector<float, 2> expected { 5.0f, 2.0f };

			// Act
			auto mv = m * v;

			// Assert
			REQUIRE(mv == expected);
		}
		SECTION("by vector") {
			// Arrange
			ml::Matrix<float, 2, 2> m { ml::Vector<float, 2>
				{ 3.0f, -2.0f },
				{ 2.0f,  1.0f }
			};
			ml::Vector<float, 2> v { 5.0f, 7.0f };
			ml::Vector<float, 2> expected { 29.0f, -3.0f };

			// Act
			auto mv = m * v;

			// Assert
			REQUIRE(mv == expected);
		}
		SECTION("by matrix") {
			// Arrange
			ml::Matrix<float, 2, 2> expected { ml::Vector<float, 2>
				{ 2.0f,  1.0f },
				{ 0.0f, -2.0f }
			};
			ml::Matrix<float, 2, 2> m1 { ml::Vector<float, 2>
				{  1.0f, 1.0f },
				{ -2.0f, 0.0f }
			};
			ml::Matrix<float, 2, 2> m2 { ml::Vector<float, 2>
				{ 0.0f, 1.0f },
				{ 2.0f, 0.0f }
			};

			// Act
			auto result = m2 * m1;

			// Assert
			REQUIRE(result == expected);
		}
	}
}

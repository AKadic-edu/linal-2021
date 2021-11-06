#include <mathlib/matrix.hpp>
#include <mathlib/vector.hpp>

#include "mathlib.hpp"

TEST_CASE("Basis") {
	SECTION("basis vectors") {
		SECTION("can be multiplied by scalars") {
			// Arrange
			float a = 5.0f;
			float b = 2.0f;
			ml::Vector<float, 2> expected { a, b };
			ml::Vector<float, 2> i { 1.0f, 0.0f };
			ml::Vector<float, 2> j { 0.0f, 1.0f };

			// Act
			ml::Vector<float, 2> c { a * i + b * j };

			// Assert
			REQUIRE(c == expected);
		}
	}
	SECTION("basis matrix") {
		SECTION("can be multiplied by vector") {
			// Arrange
			float a = 5.0f;
			float b = 2.0f;
			ml::Vector<float, 2> expected { a, b };
			ml::Matrix<float, 2, 2> basis { ml::Vector<float, 2>
				{ 1.0f, 0.0f },
				{ 0.0f, 1.0f }
			};
			ml::Vector<float, 2> v { a, b };

			// Act
			auto result = basis * v;

			// Assert
			REQUIRE(result == expected);
		}

		SECTION("can be multiplied by by matrix") {
			// Arrange
			float a = 5.0f;
			float b = 2.0f;
			ml::Matrix<float, 2, 2> expected { ml::Vector<float, 2>
				{ a, 0.0f },
				{ 0.0f, b }
			};
			ml::Matrix<float, 2, 2> basis { ml::Vector<float, 2>
				{ 1.0f, 0.0f },
				{ 0.0f, 1.0f }
			};
			ml::Matrix<float, 2, 2> m { ml::Vector<float, 2>
				{ a, 0.0f },
				{ 0.0f, b }
			};

			// Act
			auto result = m * basis;

			// Assert
			REQUIRE(result == expected);
		}
	}
}

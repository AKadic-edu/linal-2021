#include <mathlib/matrix.hpp>
#include <mathlib/vector.hpp>
#include <mathlib/utils/operations.hpp>

#include "mathlib.hpp"

TEST_CASE("Operations") {
	SECTION("Vector") {
		SECTION("cross") {
			// Arrange
			ml::Vector<float, 3> expected { 54.0f, -8.0f, -52.0f };
			ml::Vector<float, 3> a { 2.0f, 7.0f, 1.0f };
			ml::Vector<float, 3> b { 8.0f, 2.0f, 8.0f };

			// Act
			auto result = ml::cross(a, b);

			// Assert
			REQUIRE(result == expected);
		}

		SECTION("dot") {
			// Arrange
			float expected = 2.0f * 8.0f + 7.0f * 2.0f + 1.0f * 8.0f;
			ml::Vector<float, 3> a{ 2.0f, 7.0f, 1.0f };
			ml::Vector<float, 3> b{ 8.0f, 2.0f, 8.0f };

			// Act
			auto result = ml::dot(a, b);

			// Assert
			REQUIRE(result == expected);
		}
	}

	SECTION("Matrix") {
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

		SECTION("determinant") {
			SECTION("2x2 matrix") {
				// Arrange
				float expected = 1.0f * 4.0f - 3.0f * 2.0f;
				ml::Matrix<float, 2, 2> m { ml::Vector<float, 2>
					{ 1.0f, 2.0f },
					{ 3.0f, 4.0f },
				};

				// Act
				auto result = ml::determinant(m);

				// Assert
				REQUIRE(result == expected);
			}

			SECTION("3x3 matrix") {
				// Arrange
				auto expected = 0.0f;
				ml::Matrix<float, 3, 3> m { ml::Vector<float, 3>
					{ 1.0f, 2.0f, 3.0f },
					{ 4.0f, 5.0f, 6.0f },
					{ 7.0f, 8.0f, 9.0f }
				};
				ml::Matrix<float, 2, 2> m1 { ml::Vector<float, 2>
					{ m[1][1], m[1][2] },
					{ m[2][1], m[2][2] }
				};
				ml::Matrix<float, 2, 2> m2 { ml::Vector<float, 2>
					{ m[0][1], m[0][2] },
					{ m[2][1], m[2][2] }
				};
				ml::Matrix<float, 2, 2> m3 { ml::Vector<float, 2>
					{ m[0][1], m[0][2] },
					{ m[1][1], m[1][2] }
				};

				// Act
				auto result = ml::determinant(m);

				// Assert
				REQUIRE(result == expected);
			}
		}

		SECTION("inverse") {
			// Arrange
			auto expected = ml::identity<float, 3, 3>();
			ml::Matrix<float, 3, 3> m { ml::Vector<float, 3>
				{ 1.0f, 2.0f, 3.0f },
				{ 4.0f, 5.0f, 6.0f },
				{ 7.0f, 8.0f, 9.0f }
			};

			// Act
			auto result = ml::inverse(m);

			// Assert
			REQUIRE(result == expected);
		}
	}
}

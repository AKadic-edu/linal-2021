#include <mathlib/vector.hpp>

#include "mathlib.hpp"

TEST_CASE("Vector", "[Vector]") {
    SECTION("can be created") {
        SECTION("with int") {
            // Arrange
            const int size { 4 };
            int a { 54 };
            int b { 34 };
            int c { 63415 };
            int d { 43952345 };

            // Act
            ml::Vector<int, size> v { a, b, c, d };

            // Assert
            auto actual = (sizeof(v.v) / sizeof(*v.v));

            REQUIRE(size == actual);
            REQUIRE(v.v[0] == a);
            REQUIRE(v.v[1] == b);
            REQUIRE(v.v[2] == c);
            REQUIRE(v.v[3] == d);
        }
        SECTION("with float") {
            // Arrange
            const int size { 4 };
            float a { 0.7345f };
            float b { 1.421f };
            float c { 2.62345f };
            float d { 3.5245f };

            // Act
            ml::Vector<float, size> v { a, b, c, d };

            // Assert
            auto actual = (sizeof(v.v) / sizeof(*v.v));

            REQUIRE(size == actual);
            REQUIRE(v.v[0] == a);
            REQUIRE(v.v[1] == b);
            REQUIRE(v.v[2] == c);
            REQUIRE(v.v[3] == d);
        }
    }

    SECTION("can be added") {
        SECTION("with type int") {
            // Arrange
            const int size { 4 };
            int a1 { 41234 };
            int b1 { 54213 };
            int c1 { 435234 };
            int d1 { 86785 };
            int a2 { 3245 };
            int b2 { 5643 };
            int c2 { 356234 };
            int d2 { 2435435 };
            ml::Vector<int, size> v1 { a1, b1, c1, d1 };
            ml::Vector<int, size> v2 { a2, b2, c2, d2 };

            // Act
            auto v3 = v1 + v2;

            // Assert
            auto actual = (sizeof(v3.v) / sizeof(*v3.v));

            REQUIRE(size == actual);
            REQUIRE(v3.v[0] == a1 + a2);
            REQUIRE(v3.v[1] == b1 + b2);
            REQUIRE(v3.v[2] == c1 + c2);
            REQUIRE(v3.v[3] == d1 + d2);
        }
        SECTION("with type float") {
            // Arrange
            const int size { 3 };
            float a1 { 0.7345f };
            float b1 { 1.421f };
            float c1 { 2.62345f };
            float a2 { 0.9234f };
            float b2 { 1.4214f };
            float c2 { 2.0472341f };
            ml::Vector<float, size> v1 { a1, b1, c1 };
            ml::Vector<float, size> v2 { a2, b2, c2 };

            // Act
            auto v3 = v1 + v2;

            // Assert
            auto actual = (sizeof(v3.v) / sizeof(*v3.v));

            REQUIRE(size == actual);
            REQUIRE(v3.v[0] == a1 + a2);
            REQUIRE(v3.v[1] == b1 + b2);
            REQUIRE(v3.v[2] == c1 + c2);
        }
    }

    SECTION("can be subtracted") {
        SECTION("with type int") {
            // Arrange
            const int size{ 4 };
            int a1 { 9345 };
            int b1 { 98345 };
            int c1 { 832452345 };
            int d1 { 52341234 };
            int a2 { 2134 };
            int b2 { 234 };
            int c2 { 783453425 };
            int d2 { 823412 };
            ml::Vector<int, size> v1 { a1, b1, c1, d1 };
            ml::Vector<int, size> v2 { a2, b2, c2, d2 };

            // Act
            auto v3 = v1 - v2;

            // Assert
            auto actual = (sizeof(v3.v) / sizeof(*v3.v));

            REQUIRE(size == actual);
            REQUIRE(v3.v[0] == a1 - a2);
            REQUIRE(v3.v[1] == b1 - b2);
            REQUIRE(v3.v[2] == c1 - c2);
            REQUIRE(v3.v[3] == d1 - d2);
        }
        SECTION("with type float") {
            // Arrange
            const int size { 3 };
            float a1 { 0.874574f };
            float b1 { 1.4325f };
            float c1 { 2.0f };
            float a2 { 0.3475f };
            float b2 { 1.93124845f };
            float c2 { 2.9834523f };
            ml::Vector<float, size> v1{ a1, b1, c1 };
            ml::Vector<float, size> v2{ a2, b2, c2 };

            // Act
            auto v3 = v1 - v2;

            // Assert
            auto actual = (sizeof(v3.v) / sizeof(*v3.v));

            REQUIRE(size == actual);
            REQUIRE(v3.v[0] == a1 - a2);
            REQUIRE(v3.v[1] == b1 - b2);
            REQUIRE(v3.v[2] == c1 - c2);
        }
    }

    SECTION("can be multiplied") {
        SECTION("with type float") {
            // Arrange
            const int size { 6 };
            float a1 { 0.874574f };
            float b1 { 1.4325f };
            float c1 { 2.0f };
            float d1 { 2.942134f };
            float e1 { 1234.4123423f };
            float f1 { 43214.12341234f };
            float a2 { 0.3475f };
            float b2 { 1234.934123424845f };
            float c2 { 4.9352143f };
            float d2 { 214.44523f };
            float e2 { 143214.123432f };
            float f2 { 214.9834523f };
            ml::Vector<float, size> v1 { a1, b1, c1, d1, e1, f1 };
            ml::Vector<float, size> v2 { a2, b2, c2, d2, e2, f2 };

            // Act
            auto v3 = v1 * v2;

            // Assert
            auto actual = (sizeof(v3.v) / sizeof(*v3.v));

            REQUIRE(size == actual);
            REQUIRE(v3[0] == a1 * a2);
            REQUIRE(v3[1] == b1 * b2);
            REQUIRE(v3[2] == c1 * c2);
            REQUIRE(v3[3] == d1 * d2);
            REQUIRE(v3[4] == e1 * e2);
            REQUIRE(v3[5] == f1 * f2);
        }
    }

    SECTION("can be scaled (multiplied)") {
        SECTION("with type int") {
            // Arrange
            const int size { 4 };
            int a { 9345 };
            int b { 98345 };
            int c { 8324 };
            int d { 523414 };
            int s { 7 };
            ml::Vector<int, size> v { a, b, c, d };

            // Act
            auto actual = v * s;

            // Assert
            auto actualSize = (sizeof(actual.v) / sizeof(*actual.v));

            REQUIRE(size == actualSize);
            REQUIRE(actual[0] == a * s);
            REQUIRE(actual[1] == b * s);
            REQUIRE(actual[2] == c * s);
            REQUIRE(actual[3] == d * s);
        }
        SECTION("with type float") {
            // Arrange
            const int size { 3 };
            float a { 0.874574f };
            float b { 1.4325f };
            float c { 2.0f };
            float s { 7.0f };
            ml::Vector<float, size> v { a, b, c, };

            // Act
            auto actual1 = v * s;
            auto actual2 = s * v;

            // Assert
            auto actual1Size = (sizeof(actual1.v) / sizeof(*actual1.v));
            auto actual2Size = (sizeof(actual2.v) / sizeof(*actual2.v));

            REQUIRE(size == actual1Size);
            REQUIRE(actual1[0] == a * s);
            REQUIRE(actual1[1] == b * s);
            REQUIRE(actual1[2] == c * s);
            REQUIRE(size == actual2Size);
            REQUIRE(actual2[0] == a * s);
            REQUIRE(actual2[1] == b * s);
            REQUIRE(actual2[2] == c * s);
        }
    }

    SECTION("can be scaled (divided)") {
        SECTION("with type float") {
            // Arrange
            const int size { 4 };
            float a { 0.7345f };
            float b { 1.421f };
            float c { 2.62345f };
            float d { 3.5245f };
            int s { 7 };
            ml::Vector<float, size> v { a, b, c, d };

            // Act
            auto actual = v / s;

            // Assert
            auto actualSize = (sizeof(actual.v) / sizeof(*actual.v));

            REQUIRE(size == actualSize);
            REQUIRE(actual[0] == a / s);
            REQUIRE(actual[1] == b / s);
            REQUIRE(actual[2] == c / s);
            REQUIRE(actual[3] == d / s);
        }
    }
}

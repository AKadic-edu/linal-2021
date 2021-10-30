#include <mathlib/vector.hpp>

#include "mathlib.hpp"

TEST_CASE("Vector") {
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
}

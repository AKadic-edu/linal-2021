#include "src/videolib/utils/coordinate_helper.hpp"

#include "videolib.hpp"

#include <mathlib/vector.hpp>

typedef std::vector<std::tuple<std::string, ml::Vector<float, 2>, std::string, ml::Vector<int, 2>>> TestCoordinates;

SCENARIO("Conversion of window coordinates") {
    std::vector<std::tuple<ml::Vector<int, 2>, TestCoordinates>> testData {
        { { 640, 480 },
            {
                { "top-left",       { -1.0f,  1.0f }, "(0, 0)",     {   0, 0   } },
                { "top-right",      {  1.0f,  1.0f }, "(640, 0)",   { 640, 0   } },
                { "bottom-left",    { -1.0f, -1.0f }, "(0, 480)",   {   0, 480 } },
                { "bottom-right",   {  1.0f, -1.0f }, "(640, 480)", { 640, 480 } },
                { "center-center",  {  0.0f,  0.0f }, "(320, 240)", { 320, 240 } }
            }
        },
        { { 1920, 1080 },
            {
                { "top-left",       { -1.0f,  1.0f }, "(0, 0)",       {    0, 0    } },
                { "top-right",      {  1.0f,  1.0f }, "(1920, 0)",    { 1920, 0    } },
                { "bottom-left",    { -1.0f, -1.0f }, "(0, 1080)",    {    0, 1080 } },
                { "bottom-right",   {  1.0f, -1.0f }, "(1920, 1080)", { 1920, 1080 } },
                { "center-center",  {  0.0f,  0.0f }, "(320, 1080)",  {  320, 240  } }
            }
        },
    };

    for (const auto& data : testData) {
        auto& screenSize { std::get<0>(data) };
        auto& testCoordinates { std::get<1>(data) };

        for (const auto& testCoordinate : testCoordinates) {
            GIVEN("relative " + std::get<0>(testCoordinate) + " screen coordinates") {
                const auto& normalized { std::get<1>(testCoordinate) };

                WHEN("converting to pixel coordinates") {
                    const auto actual { vl::CoordinateHelper::toPixels(screenSize, normalized) };

                    THEN("returns " + std::get<2>(testCoordinate)) {
                        const auto& expected { std::get<3>(testCoordinate) };

                        REQUIRE(actual[0] == expected[0]);
                        REQUIRE(actual[1] == expected[1]);
                    }
                }
            }
        }
    }

    ml::Vector<int, 2> viewport { 640, 480 };

    GIVEN("pixel top-left screen coordinates") {
        ml::Vector<int, 2> pixels { 0, 0 };

        WHEN("Converting to pixel coordinates") {
            ml::Vector<int, 2> actual = vl::CoordinateHelper::toRelative(viewport, pixels);

            THEN("Returns (-1, 1)") {
                ml::Vector<float, 2> expected { -1.0f, 1.0f };

                REQUIRE(actual[0] == expected[0]);
                REQUIRE(actual[1] == expected[1]);
            }
        }
    }

    GIVEN("pixel top-right screen coordinates") {
        ml::Vector<int, 2> pixels { viewport[0], 0 };

        WHEN("Converting to pixel coordinates") {
            ml::Vector<int, 2> actual = vl::CoordinateHelper::toRelative(viewport, pixels);

            THEN("Returns (1, 1)") {
                ml::Vector<float, 2> expected { 1.0f, 1.0f };

                REQUIRE(actual[0] == expected[0]);
                REQUIRE(actual[1] == expected[1]);
            }
        }
    }

    GIVEN("pixel bottom-left screen coordinates") {
        ml::Vector<int, 2> pixels { 0, viewport[1] };

        WHEN("Converting to pixel coordinates") {
            ml::Vector<int, 2> actual = vl::CoordinateHelper::toRelative(viewport, pixels);

            THEN("Returns (-1, -1)") {
                ml::Vector<float, 2> expected { -1.0f, -1.0f };

                REQUIRE(actual[0] == expected[0]);
                REQUIRE(actual[1] == expected[1]);
            }
        }
    }

    GIVEN("pixel bottom-right screen coordinates") {
        ml::Vector<int, 2> pixels { viewport[0], viewport[1] };

        WHEN("Converting to pixel coordinates") {
            ml::Vector<int, 2> actual = vl::CoordinateHelper::toRelative(viewport, pixels);

            THEN("Returns (-1, 1)") {
                ml::Vector<float, 2> expected { 1.0f, -1.0f };

                REQUIRE(actual[0] == expected[0]);
                REQUIRE(actual[1] == expected[1]);
            }
        }
    }

    GIVEN("pixel center screen coordinates") {
        ml::Vector<int, 2> pixels { viewport[0] / 2, viewport[1] / 2 };

        WHEN("Converting to pixel coordinates") {
            ml::Vector<int, 2> actual = vl::CoordinateHelper::toRelative(viewport, pixels);

            THEN("Returns (0, 0)") {
                ml::Vector<float, 2> expected { 0.0f, 0.0f };

                REQUIRE(actual[0] == expected[0]);
                REQUIRE(actual[1] == expected[1]);
            }
        }
    }
}

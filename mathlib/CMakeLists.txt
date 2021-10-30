add_library(mathlib INTERFACE)

target_include_directories(mathlib
	INTERFACE "${CMAKE_CURRENT_LIST_DIR}/include")

ADD_EXECUTABLE(mathlib_tests
	"test/001_vector.cpp")

target_include_directories(mathlib_tests
	PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(mathlib_tests PRIVATE mathlib)

find_package(Catch2 CONFIG REQUIRED)
target_link_libraries(mathlib_tests PRIVATE Catch2::Catch2)
target_compile_definitions(mathlib_tests PRIVATE CATCH_CONFIG_MAIN)

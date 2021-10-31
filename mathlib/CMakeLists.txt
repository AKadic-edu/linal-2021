set(PROJECT_NAME mathlib)
set(PROJECT_TEST_NAME ${PROJECT_NAME}_tests)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME}
	INTERFACE "${CMAKE_CURRENT_LIST_DIR}/include")

add_executable(${PROJECT_TEST_NAME}
	"test/000_catch_main.cpp"
	"test/001_vector.cpp"
	"test/002_matrix.cpp")
	
target_include_directories(${PROJECT_TEST_NAME}
	PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(${PROJECT_TEST_NAME} PRIVATE ${PROJECT_NAME})

find_package(Catch2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_TEST_NAME} PRIVATE Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(${PROJECT_TEST_NAME})

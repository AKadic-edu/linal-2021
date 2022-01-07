set(PROJECT_NAME videolib)
set(PROJECT_TEST_NAME ${PROJECT_NAME}_tests)

add_library(${PROJECT_NAME} STATIC
	"src/videolib/instance.cpp"
	"src/videolib/model.cpp"
	"src/videolib/renderer.cpp"
	"src/videolib/utils/coordinate_helper.cpp")

target_include_directories(${PROJECT_NAME}
	PRIVATE ${CMAKE_CURRENT_LIST_DIR}
	INTERFACE "${CMAKE_CURRENT_LIST_DIR}/include")
	
target_link_libraries(${PROJECT_NAME} PUBLIC mathlib)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL2::SDL2 SDL2::SDL2main)

add_executable(${PROJECT_TEST_NAME}
	"test/001_coordinate_helper.cpp")

target_include_directories(${PROJECT_TEST_NAME}
	PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_compile_definitions(${PROJECT_TEST_NAME} PRIVATE SDL_MAIN_HANDLED)
target_link_libraries(${PROJECT_TEST_NAME} PRIVATE ${PROJECT_NAME})


find_package(Catch2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_TEST_NAME} PRIVATE Catch2::Catch2)
target_compile_definitions(${PROJECT_TEST_NAME} PRIVATE CATCH_CONFIG_MAIN)

include(CTest)
include(Catch)
catch_discover_tests(${PROJECT_TEST_NAME})

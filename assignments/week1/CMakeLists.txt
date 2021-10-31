set(PROJECT_NAME week1)
set(PROJECT_TEST_NAME ${PROJECT_NAME}_tests)

add_executable(${PROJECT_NAME}
	"src/main.cpp")

target_include_directories(${PROJECT_NAME}
	PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE mathlib)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)

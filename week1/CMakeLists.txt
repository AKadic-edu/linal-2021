add_executable(Week1
	"src/main.cpp")

target_link_directories(Week1
	PRIVATE ${CMAKE_CURRENT_LIST_DIR})

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(Week1 PRIVATE SDL2::SDL2 SDL2::SDL2main)
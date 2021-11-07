set(PROJECT_NAME Final)
set(PROJECT_TEST_NAME ${PROJECT_NAME}Tests)

add_executable(${PROJECT_NAME}
	"src/main.cpp")

target_include_directories(${PROJECT_NAME}
	PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(${PROJECT_NAME}
	PRIVATE videolib)

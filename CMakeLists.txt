cmake_minimum_required(VERSION 3.25)

add_subdirectory(modules/http_parser)

option(OWQL_TESTS "Enable testing")

project(OWQL)

find_package(spdlog REQUIRED)

add_library(OWQL
		src/server.cpp
	)

target_include_directories(OWQL PUBLIC include PRIVATE include/OWQL)
target_link_libraries(OWQL PUBLIC spdlog::spdlog http_parser)

# tests

#if(${OWQL_TESTS})
enable_testing()
#endif()

file(GLOB TESTS "tests/*.cpp" "tests/*.c")

foreach(TEST ${TESTS})
	get_filename_component(TEST_NAME ${TEST} NAME_WE)
	add_executable(${TEST_NAME} ${TEST})
	target_link_libraries(${TEST_NAME} OWQL) 
	add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()


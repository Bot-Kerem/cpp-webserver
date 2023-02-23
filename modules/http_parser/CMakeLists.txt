cmake_minimum_required(VERSION 3.25)

project(http_parser)

add_library(http_parser src/parser.cpp)
target_include_directories(http_parser PRIVATE include/http_parser PUBLIC include)


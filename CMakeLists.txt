cmake_minimum_required(VERSION 2.6)
project(monitor)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_subdirectory(thirdparty/googletest)

add_executable(monitor ${SOURCES})

add_executable(test_linux_parser test/test_linux_parser.cpp src/linux_parser.cpp)

target_link_libraries(test_linux_parser
        gtest_main
        )


set_property(TARGET monitor PROPERTY CXX_STANDARD 17)
set_property(TARGET test_linux_parser PROPERTY CXX_STANDARD 17)
target_link_libraries(monitor ${CURSES_LIBRARIES})
# TODO: Run -Werror in CI.
target_compile_options(monitor PRIVATE -Wall -Wextra)

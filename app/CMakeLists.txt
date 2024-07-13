# Author: Hyunseo Park
#
# Description:
#
cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(pcu VERSION 0.0.0)

zephyr_library_link_libraries(kernel)

#project(app LANGUAGES C VERSION 1.0.0)

# if we want separate directory for .hpp
#target_include_directories(app PRIVATE ${CMAKE_BINARY_DIR}/app/include src)

# Entry point
target_sources(app PRIVATE src/main.cpp)

# Subdirectories
# add_subdirectory(src/common)
include(utils.cmake)
cmake_minimum_required(VERSION 3.16)
add_subdirectory(tinygltf)

executable(game src/*.cpp)

precompile_headers(game src/pch.h)
compile_options(game -std:c++20 -wd4244)
link(game d3d11.lib d3dcompiler.lib ws2_32.lib tinygltf)

pre_build(game python scripts/pre_build.py ${CMAKE_BUILD_TYPE})
post_build(game python scripts/post_build.py ${CMAKE_BUILD_TYPE})
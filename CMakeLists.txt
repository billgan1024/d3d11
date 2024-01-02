cmake_minimum_required(VERSION 3.16)

function(precompile_headers target header...)
  list(POP_FRONT ARGV)

  target_precompile_headers(${target} PRIVATE ${ARGV})
endfunction()

function(executable name pattern...)
  list(POP_FRONT ARGV)

  foreach(pattern ${ARGV})
    file(GLOB src CONFIGURE_DEPENDS ${pattern})
    add_executable(${name} ${src})
  endforeach()
endfunction()

function(link name libs...)
  list(POP_FRONT ARGV)
  target_link_libraries(${name} PRIVATE ${ARGV})
endfunction()

function(compile_options name option...)
  list(POP_FRONT ARGV)
  target_compile_options(${name} PRIVATE ${ARGV})
endfunction()

function(pre_build name command)
  list(POP_FRONT ARGV)
  add_custom_command(TARGET ${name} PRE_BUILD COMMAND ${ARGV} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endfunction()

function(post_build name command)
  list(POP_FRONT ARGV)
  add_custom_command(TARGET ${name} POST_BUILD COMMAND ${ARGV} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endfunction()

# ==================================================================================================

add_subdirectory(tinygltf)

executable(game src/*.cpp)

precompile_headers(game src/pch.h)
compile_options(game -std:c++20 -wd4244)
link(game d3d11.lib d3dcompiler.lib ws2_32.lib tinygltf)

pre_build(game python scripts/pre_build.py ${CMAKE_BUILD_TYPE})
post_build(game python scripts/post_build.py ${CMAKE_BUILD_TYPE})
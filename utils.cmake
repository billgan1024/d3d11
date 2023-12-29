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
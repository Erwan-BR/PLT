set(lib_constants_target constants_static)

# Generate header files from dia UML files
generate_dia_header("${CMAKE_CURRENT_SOURCE_DIR}/../constants.dia")

# Find all source files to compile into a library
file(GLOB_RECURSE constants_sources *.cpp)

# Build the "constants" library and add required includes
add_library(${lib_constants_target} STATIC ${constants_sources} ${jsoncpp_sources})
add_dependencies(${lib_constants_target} generate-headers)
target_include_directories(${lib_constants_target} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${jsoncpp_include_dir}
  )

# vim: set sw=2 sts=2 et:

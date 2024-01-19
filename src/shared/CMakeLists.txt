set(lib_shared_target shared_static)

# Generate header files from dia UML files
generate_dia_header("${CMAKE_CURRENT_SOURCE_DIR}/../state.dia")
generate_dia_header("${CMAKE_CURRENT_SOURCE_DIR}/../engine.dia")
generate_dia_header("${CMAKE_CURRENT_SOURCE_DIR}/../ai.dia")

# Find all source files to include in library
file(GLOB_RECURSE shared_sources *.cpp)

# Build the "shared" library, add required include and link against dependencies
add_library(${lib_shared_target} STATIC ${shared_sources} ${jsoncpp_sources})
add_dependencies(${lib_shared_target} generate-headers)
target_include_directories(${lib_shared_target} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${SFML_INCLUDE_DIR}
  ${jsoncpp_include_dir}
  )
target_link_libraries(${lib_shared_target} PUBLIC
  ${SFML_LIBRARIES}
  $<TARGET_NAME:constants_static>
  )

# vim: set sw=2 sts=2 et:
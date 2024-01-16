# # Generate header and source files from dia UML files
# generate_dia_header("${CMAKE_CURRENT_SOURCE_DIR}/../constants.dia")

# # Find all source files to compile into a library
# file(GLOB_RECURSE constant_sources *.cpp)

# # Create a library for constants
# add_library(constants_library STATIC ${constant_sources})
# target_include_directories(constants_library PUBLIC
#   ${CMAKE_CURRENT_SOURCE_DIR}
# )

# # Export the target for use in other CMakeLists.txt files
# export(TARGETS constants_library FILE ConstantsLibraryConfig.cmake)

# # vim: set sw=2 sts=2 et:

# Generate header and source files from dia UML files
generate_dia_header("${CMAKE_CURRENT_SOURCE_DIR}/../constants.dia")

# Add the generated header file to the list of source files
set(constant_sources ${CMAKE_CURRENT_BINARY_DIR}/constants_generated.h)

# Find all other source files to compile into a library
file(GLOB_RECURSE constant_sources ${constant_sources} *.cpp)

# Create a library for constants
add_library(constants_library STATIC ${constant_sources})
target_include_directories(constants_library PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}  # Include the binary directory for the generated header
)

# Export the target for use in other CMakeLists.txt files
export(TARGETS constants_library FILE ConstantsLibraryConfig.cmake)

# vim: set sw=2 sts=2 et:

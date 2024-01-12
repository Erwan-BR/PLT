# Generate header files from dia UML files
generate_dia_header("${CMAKE_CURRENT_SOURCE_DIR}/../constants.dia")

# Create an interface library for constants
add_library(constants_interface INTERFACE)
target_include_directories(constants_interface INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# Export the target for use in other CMakeLists.txt files
export(TARGETS constants_interface FILE ConstantsLibraryConfig.cmake)

# vim: set sw=2 sts=2 et:

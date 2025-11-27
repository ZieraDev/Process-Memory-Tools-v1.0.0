cmake_minimum_required(VERSION 3.15)
project(ProcessMemoryTools VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Compiler flags
if(MSVC)
    add_compile_options(/W4 /WX-)
    # Request administrator privileges
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\"")
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Utility library
add_library(ProcessUtils STATIC
    src/process_utils.cpp
    include/process_utils.h
)

# Process Modifier executable
add_executable(ProcessModifier
    src/process_modifier.cpp
)
target_link_libraries(ProcessModifier ProcessUtils psapi)

# Window Controller executable
add_executable(WindowController
    src/window_controller.cpp
)
target_link_libraries(WindowController ProcessUtils user32)

# Installation
install(TARGETS ProcessModifier WindowController
    RUNTIME DESTINATION bin
)

install(FILES
    README.md
    LICENSE
    DESTINATION .
)

# Print build info
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")

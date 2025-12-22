cmake_minimum_required(VERSION 3.16)

project(auraloid_engine
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Engine source files
file(GLOB_RECURSE AURALOID_ENGINE_SOURCES
    core/*.cpp
)

file(GLOB_RECURSE AURALOID_ENGINE_HEADERS
    core/*.h
)

add_library(auraloid_engine STATIC
    ${AURALOID_ENGINE_SOURCES}
    ${AURALOID_ENGINE_HEADERS}
)

target_include_directories(auraloid_engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/core
)

# Platform-specific settings
if(WIN32)
    target_compile_definitions(auraloid_engine PRIVATE AURALOID_PLATFORM_WINDOWS)
elseif(APPLE)
    target_compile_definitions(auraloid_engine PRIVATE AURALOID_PLATFORM_MACOS)
elseif(UNIX)
    target_compile_definitions(auraloid_engine PRIVATE AURALOID_PLATFORM_LINUX)
endif()

# Warnings
if(MSVC)
    target_compile_options(auraloid_engine PRIVATE /W4)
else()
    target_compile_options(auraloid_engine PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Future external dependencies (FLAC, ONNX, etc.)
# add_subdirectory(external/flac)
# target_link_libraries(auraloid_engine PRIVATE flac)

message(STATUS "Auraloid Engine configured")


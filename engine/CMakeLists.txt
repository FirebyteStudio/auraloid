cmake_minimum_required(VERSION 3.16)

project(auraloid_engine
    VERSION 0.3.0
    LANGUAGES CXX
)

# =========================
# C++ settings
# =========================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# =========================
# Output directories
# =========================
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# =========================
# ONNX Runtime
# =========================
set(ONNXRUNTIME_ROOT "" CACHE PATH "ONNX Runtime root directory")

if(NOT ONNXRUNTIME_ROOT)
    message(FATAL_ERROR "ONNXRUNTIME_ROOT not set (path to ONNX Runtime)")
endif()

# =========================
# Engine source files
# =========================
file(GLOB_RECURSE AURALOID_ENGINE_SOURCES
    core/*.cpp
)

file(GLOB_RECURSE AURALOID_ENGINE_HEADERS
    core/*.h
)

# =========================
# Library
# =========================
add_library(auraloid_engine STATIC
    ${AURALOID_ENGINE_SOURCES}
    ${AURALOID_ENGINE_HEADERS}
)

# =========================
# Includes
# =========================
target_include_directories(auraloid_engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/core
        ${ONNXRUNTIME_ROOT}/include
)

# =========================
# Link directories
# =========================
target_link_directories(auraloid_engine
    PRIVATE
        ${ONNXRUNTIME_ROOT}/lib
)

target_link_libraries(auraloid_engine
    PRIVATE
        onnxruntime
)

# =========================
# Platform-specific defines
# =========================
if(WIN32)
    target_compile_definitions(auraloid_engine PRIVATE AURALOID_PLATFORM_WINDOWS)
elseif(APPLE)
    target_compile_definitions(auraloid_engine PRIVATE AURALOID_PLATFORM_MACOS)
elseif(UNIX)
    target_compile_definitions(auraloid_engine PRIVATE AURALOID_PLATFORM_LINUX)
endif()

# =========================
# Warnings
# =========================
if(MSVC)
    target_compile_options(auraloid_engine PRIVATE /W4)
else()
    target_compile_options(auraloid_engine PRIVATE -Wall -Wextra -Wpedantic)
endif()

# =========================
# Future external deps
# =========================
# add_subdirectory(external/flac)
# target_link_libraries(auraloid_engine PRIVATE flac)

message(STATUS "Auraloid Engine configured with ONNX Runtime")



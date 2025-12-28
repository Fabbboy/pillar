cmake_minimum_required(VERSION 4.2)
project(pillar C CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(PillarPlatform)
include(PillarBits)
include(PillarCompiler)

pillar_detect_platform()
pillar_detect_bits()
pillar_detect_compiler()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(PILLAR_CONFIG_TEMPLATE "${CMAKE_SOURCE_DIR}/config.h.in")
set(PILLAR_CONFIG_TARGET "${CMAKE_BINARY_DIR}/config.h")

configure_file(
    ${PILLAR_CONFIG_TEMPLATE}
    ${PILLAR_CONFIG_TARGET}
)

set(PILLAR_INCLUDE "${CMAKE_SOURCE_DIR}/include")
include_directories(${PILLAR_INCLUDE})
include_directories(${CMAKE_BINARY_DIR})

set(PILLAR_C_SOURCES
    src/pillar-c/status.c
    src/pillar-c/intrin.c
    src/pillar-c/types.c
    src/pillar-c/allocator.c
    src/pillar-c/system.c
    src/pillar-c/vec.c
)

set(PILLAR_CXX_SOURCES
    src/pillar/placeholder.cc
)

add_library(pillar-c STATIC ${PILLAR_C_SOURCES})
set_target_properties(pillar-c PROPERTIES LINKER_LANGUAGE C)

add_library(pillar-cxx STATIC ${PILLAR_CXX_SOURCES})
set_target_properties(pillar-cxx PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(pillar-cxx pillar-c)

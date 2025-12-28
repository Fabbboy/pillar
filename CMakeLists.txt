cmake_minimum_required(VERSION 4.2)
project(pillar CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(PillarPlatform)
include(PillarBits)
include(PillarCompiler)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(PILLAR_CONFIG_TEMPLATE "${CMAKE_SOURCE_DIR}/config.h.in")
set(PILLAR_CONFIG_TARGET "${CMAKE_BINARY_DIR}/config.h")

configure_file(
    ${PILLAR_CONFIG_TEMPLATE}
    ${PILLAR_CONFIG_TARGET}
)
cmake_minimum_required(VERSION 4.2)
project(pillar CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(PillarPlatform)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

function(on_posix)
    message(STATUS "Configuring for a POSIX platform")
endfunction(on_posix)

pillar_run_on_posix(on_posix)

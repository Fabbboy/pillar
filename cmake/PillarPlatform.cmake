set(PILLAR_IS_LINUX FALSE)
set(PILLAR_IS_MACOS FALSE)
set(PILLAR_IS_WINDOWS FALSE)
set(PILLAR_IS_BSD FALSE)

set(PILLAR_LINUX_PLATFORMS "Linux")
set(PILLAR_MACOS_PLATFORMS "Darwin")
set(PILLAR_WINDOWS_PLATFORMS "Windows" "MINGW" "MSYS" "CYGWIN")
set(PILLAR_BSD_PLATFORMS "FreeBSD" "NetBSD" "OpenBSD" "DragonFly")

if(CMAKE_SYSTEM_NAME IN_LIST PILLAR_LINUX_PLATFORMS)
    set(PILLAR_IS_LINUX TRUE)
elseif(CMAKE_SYSTEM_NAME IN_LIST PILLAR_MACOS_PLATFORMS)
    set(PILLAR_IS_MACOS TRUE)
elseif(CMAKE_SYSTEM_NAME IN_LIST PILLAR_WINDOWS_PLATFORMS)
    set(PILLAR_IS_WINDOWS TRUE)
elseif(CMAKE_SYSTEM_NAME IN_LIST PILLAR_BSD_PLATFORMS)
    set(PILLAR_IS_BSD TRUE)
endif()

set(PILLAR_IS_POSIX FALSE)
if(PILLAR_IS_LINUX OR PILLAR_IS_MACOS OR PILLAR_IS_BSD)
    set(PILLAR_IS_POSIX TRUE)
endif()

function(run_on_linux callback)
    if(NOT PILLAR_IS_LINUX)
        return()
    endif()

    cmake_language(CALL ${callback} ${ARGN})
endfunction()

function(run_on_macos callback)
    if(NOT PILLAR_IS_MACOS)
        return()
    endif()

    cmake_language(CALL ${callback} ${ARGN})
endfunction()

function(run_on_windows callback)
    if(NOT PILLAR_IS_WINDOWS)
        return()
    endif()

    cmake_language(CALL ${callback} ${ARGN})
endfunction()

function(run_on_bsd callback)
    if(NOT PILLAR_IS_BSD)
        return()
    endif()

    cmake_language(CALL ${callback} ${ARGN})
endfunction()

function(run_on_posix callback)
    if(NOT PILLAR_IS_POSIX)
        return()
    endif()

    cmake_language(CALL ${callback} ${ARGN})
endfunction()
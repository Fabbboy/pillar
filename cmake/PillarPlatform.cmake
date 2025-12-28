function(pillar_detect_platform)
    set(PILLAR_LINUX_PLATFORMS "Linux")
    set(PILLAR_MACOS_PLATFORMS "Darwin")
    set(PILLAR_WINDOWS_PLATFORMS "Windows" "MINGW" "MSYS" "CYGWIN")
    set(PILLAR_BSD_PLATFORMS "FreeBSD" "NetBSD" "OpenBSD" "DragonFly")

    set(PILLAR_IS_LINUX 0)
    set(PILLAR_IS_MACOS 0)
    set(PILLAR_IS_WINDOWS 0)
    set(PILLAR_IS_BSD 0)
    set(PILLAR_IS_POSIX 0)

    if(CMAKE_SYSTEM_NAME IN_LIST PILLAR_LINUX_PLATFORMS)
        set(PILLAR_IS_LINUX 1)
    elseif(CMAKE_SYSTEM_NAME IN_LIST PILLAR_MACOS_PLATFORMS)
        set(PILLAR_IS_MACOS 1)
    elseif(CMAKE_SYSTEM_NAME IN_LIST PILLAR_WINDOWS_PLATFORMS)
        set(PILLAR_IS_WINDOWS 1)
    elseif(CMAKE_SYSTEM_NAME IN_LIST PILLAR_BSD_PLATFORMS)
        set(PILLAR_IS_BSD 1)
    endif()

    if(PILLAR_IS_LINUX OR PILLAR_IS_MACOS OR PILLAR_IS_BSD)
        set(PILLAR_IS_POSIX 1)
    endif()

    set(PILLAR_IS_LINUX ${PILLAR_IS_LINUX} PARENT_SCOPE)
    set(PILLAR_IS_MACOS ${PILLAR_IS_MACOS} PARENT_SCOPE)
    set(PILLAR_IS_WINDOWS ${PILLAR_IS_WINDOWS} PARENT_SCOPE)
    set(PILLAR_IS_BSD ${PILLAR_IS_BSD} PARENT_SCOPE)
    set(PILLAR_IS_POSIX ${PILLAR_IS_POSIX} PARENT_SCOPE)
endfunction()

function(pillar_run_on_linux callback)
    if(NOT DEFINED PILLAR_IS_LINUX OR NOT PILLAR_IS_LINUX)
        return()
    endif()

    cmake_language(CALL ${callback} ${ARGN})
endfunction()

function(pillar_run_on_macos callback)
    if(NOT DEFINED PILLAR_IS_MACOS OR NOT PILLAR_IS_MACOS)
        return()
    endif()

    cmake_language(CALL ${callback} ${ARGN})
endfunction()

function(pillar_run_on_windows callback)
    if(NOT DEFINED PILLAR_IS_WINDOWS OR NOT PILLAR_IS_WINDOWS)
        return()
    endif()

    cmake_language(CALL ${callback} ${ARGN})
endfunction()

function(pillar_run_on_bsd callback)
    if(NOT DEFINED PILLAR_IS_BSD OR NOT PILLAR_IS_BSD)
        return()
    endif()

    cmake_language(CALL ${callback} ${ARGN})
endfunction()

function(pillar_run_on_posix callback)
    if(NOT DEFINED PILLAR_IS_POSIX OR NOT PILLAR_IS_POSIX)
        return()
    endif()

    cmake_language(CALL ${callback} ${ARGN})
endfunction()
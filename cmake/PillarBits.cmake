set(PILLAR_IS_16BIT FALSE PARENT_SCOPE)
set(PILLAR_IS_32BIT FALSE PARENT_SCOPE)
set(PILLAR_IS_64BIT FALSE PARENT_SCOPE)

set(PILLAR_16BIT_WIDTH 2)
set(PILLAR_32BIT_WIDTH 4)
set(PILLAR_64BIT_WIDTH 8)

if(CMAKE_SIZEOF_VOID_P EQUAL ${PILLAR_16BIT_WIDTH})
    set(PILLAR_IS_16BIT TRUE PARENT_SCOPE)
elseif(CMAKE_SIZEOF_VOID_P EQUAL ${PILLAR_32BIT_WIDTH})
    set(PILLAR_IS_32BIT TRUE PARENT_SCOPE)
elseif(CMAKE_SIZEOF_VOID_P EQUAL ${PILLAR_64BIT_WIDTH})
    set(PILLAR_IS_64BIT TRUE PARENT_SCOPE)
endif()

function(pillar_run_on_16bit callback)
    if(NOT PILLAR_IS_16BIT)
        return()
    endif()

    cmake_language(CALL ${callback} ${ARGN})
endfunction()

function(pillar_run_on_32bit callback)
    if(NOT PILLAR_IS_32BIT)
        return()
    endif()

    cmake_language(CALL ${callback} ${ARGN})
endfunction()

function(pillar_run_on_64bit callback)
    if(NOT PILLAR_IS_64BIT)
        return()
    endif()

    cmake_language(CALL ${callback} ${ARGN})
endfunction()

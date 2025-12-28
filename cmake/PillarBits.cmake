function(pillar_detect_bits)
    set(PILLAR_16BIT_WIDTH 2)
    set(PILLAR_32BIT_WIDTH 4)
    set(PILLAR_64BIT_WIDTH 8)

    set(PILLAR_IS_16BIT 0)
    set(PILLAR_IS_32BIT 0)
    set(PILLAR_IS_64BIT 0)

    if(CMAKE_SIZEOF_VOID_P EQUAL ${PILLAR_16BIT_WIDTH})
        set(PILLAR_IS_16BIT 1)
    elseif(CMAKE_SIZEOF_VOID_P EQUAL ${PILLAR_32BIT_WIDTH})
        set(PILLAR_IS_32BIT 1)
    elseif(CMAKE_SIZEOF_VOID_P EQUAL ${PILLAR_64BIT_WIDTH})
        set(PILLAR_IS_64BIT 1)
    endif()

    set(PILLAR_IS_16BIT ${PILLAR_IS_16BIT} PARENT_SCOPE)
    set(PILLAR_IS_32BIT ${PILLAR_IS_32BIT} PARENT_SCOPE)
    set(PILLAR_IS_64BIT ${PILLAR_IS_64BIT} PARENT_SCOPE)
endfunction()

function(pillar_run_on_16bit callback)
    if(NOT DEFINED PILLAR_IS_16BIT OR NOT PILLAR_IS_16BIT)
        return()
    endif()

    cmake_language(CALL ${callback} ${ARGN})
endfunction()

function(pillar_run_on_32bit callback)
    if(NOT DEFINED PILLAR_IS_32BIT OR NOT PILLAR_IS_32BIT)
        return()
    endif()

    cmake_language(CALL ${callback} ${ARGN})
endfunction()

function(pillar_run_on_64bit callback)
    if(NOT DEFINED PILLAR_IS_64BIT OR NOT PILLAR_IS_64BIT)
        return()
    endif()

    cmake_language(CALL ${callback} ${ARGN})
endfunction()

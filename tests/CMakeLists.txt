enable_testing()
add_subdirectory(unity)

set(TESTS
    vec_test
    intrin_test
    status_test
    allocator_test
)

foreach(TEST ${TESTS})
    add_executable(
        ${TEST}
        ${TEST}.cc
    )

    target_link_libraries(
        ${TEST}
        PRIVATE pillar-c pillar-cxx unity
    )

    add_test(
        NAME ${TEST}
        COMMAND ${TEST}
    )
endforeach()

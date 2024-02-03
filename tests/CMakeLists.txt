cmake_minimum_required(VERSION 3.10)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

enable_testing()

file(GLOB_RECURSE TEST_CPPS "${PROJECT_SOURCE_DIR}/tests/*test.cpp")

foreach (test_source ${TEST_CPPS})
    # Create a human readable name.
    get_filename_component(test_filename ${test_source} NAME)
    string(REPLACE ".cpp" "" mySTL_test_name ${test_filename})

    # Add the test target separately and as part of "make check-tests".
    add_executable(${mySTL_test_name}  ${test_source})
    target_link_libraries(${mySTL_test_name} GTest::gtest_main)


    gtest_discover_tests(${mySTL_test_name}
            EXTRA_ARGS
            --gtest_color=auto
            --gtest_output=xml:${CMAKE_BINARY_DIR}/test/${mySTL_test_name}.xml
            --gtest_catch_exceptions=0
            DISCOVERY_TIMEOUT 120
            PROPERTIES
            TIMEOUT 120
            )

    # Set test target properties and dependencies.
    set_target_properties(${mySTL_test_name}
            PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test"
            COMMAND ${mySTL_test_name}
            )
endforeach ()

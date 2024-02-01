cmake_minimum_required(VERSION 3.16)

project(MySTL)  # 定义项目名称

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(include)

enable_testing()

# deque_test
add_executable(
  deque_test
  tests/deque_test.cpp
)
target_link_libraries(
    deque_test
  GTest::gtest_main
)

# list_test
add_executable(
  list_test
  tests/list_test.cpp
)
target_link_libraries(
  list_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(deque_test)
gtest_discover_tests(list_test)

# rbTree_test
add_executable(
  rbTree_test
  tests/rbTree_test.cpp
)
target_link_libraries(
  rbTree_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(deque_test)
gtest_discover_tests(list_test)



add_executable(
  main
  main.cpp
)
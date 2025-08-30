include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(runTests test_instance.cpp)
target_link_libraries(runTests PRIVATE my_lib gtest_main)

include(GoogleTest)
gtest_discover_tests(runTests)
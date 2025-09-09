include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(runInstanceTests     test_instance.cpp)
add_executable(runBinTests          test_bin.cpp     )
add_executable(runSolutionTests     test_solution.cpp)
add_executable(runGreedyTests       test_greedy.cpp  )
add_executable(runNeighborhoodTests test_neighborhood.cpp)
target_link_libraries(runInstanceTests     PRIVATE my_lib gtest_main)
target_link_libraries(runBinTests          PRIVATE my_lib gtest_main)
target_link_libraries(runSolutionTests     PRIVATE my_lib gtest_main)
target_link_libraries(runGreedyTests       PRIVATE my_lib gtest_main)
target_link_libraries(runNeighborhoodTests PRIVATE my_lib gtest_main)

include(GoogleTest)
gtest_discover_tests(runInstanceTests    )
gtest_discover_tests(runBinTests         )
gtest_discover_tests(runSolutionTests    )
gtest_discover_tests(runGreedyTests      )
gtest_discover_tests(runNeighborhoodTests)
cmake_minimum_required(VERSION 3.16)

# Enable Testing
enable_testing()

# FETCH GOOGLE TEST
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# ADD EXECS
file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_executable(runTests ${TEST_SOURCES})

# LINK GOOGLE LIBS
target_link_libraries(runTests gtest gtest_main)

# DISCOVER TESTS
include(GoogleTest)
gtest_discover_tests(runTests)

cmake_minimum_required(VERSION 3.14)
project(BasilarTests)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add GoogleTest as a dependency and download it from Github
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB_RECURSE TEST_FILES CMAKE_CONFIGURE_DEPENDS "*.cpp")

# Add the test executable
add_executable(basilar_tests
    ${TEST_FILES}
)

# Link the GTest library to the test executable
target_link_libraries(
    basilar_tests
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(basilar_tests)

get_filename_component(SRC_DIR ../src ABSOLUTE)

file(GLOB_RECURSE SRC_FILES CMAKE_CONFIGURE_DEPENDS "${SRC_DIR}/*.cpp")
# Set the source files for the project
set(SOURCE_FILES
    ${SRC_FILES}
)

# Add the source files to the test executable
target_sources(basilar_tests PRIVATE ${SOURCE_FILES})
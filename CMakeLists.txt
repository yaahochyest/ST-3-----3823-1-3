cmake_minimum_required(VERSION 3.15)
project(ST-3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")

include_directories(include)

# ===== библиотека =====
add_library(ST-3-lib
    src/TimedDoor.cpp
)

target_include_directories(ST-3-lib PUBLIC include)

# ===== GoogleTest =====
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK ON CACHE BOOL "" FORCE)

# ===== тесты =====
add_executable(ST-3-test
    test/tests.cpp
    test/AllTests.cpp
)

target_link_libraries(ST-3-test
    ST-3-lib
    gtest
    gtest_main
    gmock
)

include(GoogleTest)
gtest_discover_tests(ST-3-test)
include(FetchContent)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.0
)

FetchContent_MakeAvailable(googletest)

include_directories(${gtest_SOURCE_DIR}/include)
include_directories(${${PROJECT_NAME}_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME}.test
  AllTests.cpp
  tests.cpp
)

target_include_directories(${PROJECT_NAME}.test
  PRIVATE
    ${${PROJECT_NAME}_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}.test
  PRIVATE
    ${PROJECT_NAME}
    GTest::gtest
    GTest::gmock
    GTest::gtest_main
)

install(TARGETS ${PROJECT_NAME}.test
        RUNTIME DESTINATION "${tool_dest}")

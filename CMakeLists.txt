cmake_minimum_required(VERSION 3.20)
project(bergmannTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.16.0.zip
)

FetchContent_MakeAvailable(googletest)

include_directories(${PROJECT_SOURCE_DIR})

add_executable(bergmannTest 
    main.cpp
    Point3D.cpp
    Vector3D.cpp
    Segment3D.cpp
)

enable_testing()

add_executable(bergmannGTests
    Point3D.cpp
    Vector3D.cpp
    Segment3D.cpp
    tests/segmentTests.cpp
)

target_link_libraries(bergmannGTests PRIVATE gtest_main gmock_main)

include(GoogleTest)
gtest_discover_tests(bergmannGTests)

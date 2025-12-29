cmake_minimum_required(VERSION 3.28)
project(ShotCallerEngineWow)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ShotCallerEngineWow 
    src/main.cpp 
    src/parser.cpp 
    src/engine.cpp 
    src/spelldb.cpp
)

target_include_directories(ShotCallerEngineWow PUBLIC include)

enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(engine_lib
    src/parser.cpp 
    src/engine.cpp 
    src/spelldb.cpp
)

target_include_directories(engine_lib PUBLIC include)

add_executable(engine_tests
    tests/parser_test.cpp
)

target_link_libraries(engine_tests
    gtest
    gtest_main
    engine_lib
)

include(GoogleTest)
gtest_discover_tests(engine_tests)

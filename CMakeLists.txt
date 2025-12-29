cmake_minimum_required(VERSION 3.28)

project(ShotCallerWow)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ShotCallerEngineWow src/main.cpp src/parser.cpp src/engine.cpp src/spell_db.cpp)

target_include_directories(ShotCallerEngineWow PUBLIC include)

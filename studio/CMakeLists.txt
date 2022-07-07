cmake_minimum_required(VERSION 3.5)
project(tas-studio)

add_subdirectory(lib/raylib)
add_subdirectory(lib/nlib)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 20)

include_directories(include)
include_directories(lib/raylib/src)
include_directories(lib/nlib/include)
include_directories(lib/nlib/lib/oead/src/include)

add_executable(tas-studio src/tas-studio.cpp src/client/Client.cpp src/client/TasClient.cpp src/ui/Scene.cpp src/ui/Camera.cpp src/file/KCollision.cpp)

find_package(Threads REQUIRED)
target_link_libraries(tas-studio PRIVATE Threads::Threads)
target_link_libraries(tas-studio PUBLIC raylib)
target_link_libraries(tas-studio PUBLIC nlib)
file(COPY res DESTINATION .)
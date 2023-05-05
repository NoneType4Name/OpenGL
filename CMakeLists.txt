cmake_minimum_required(VERSION 3.4)
set(CMAKE_CXX_STANDARD 20)
project("SomeEngenie"
        LANGUAGES CXX
        VERSION 1.0.0
        )
set(EXECUTABLE_NAME "window")
message("${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_VERSION}\n${CMAKE_PROJECT_DESCRIPTION}")
find_package(OpenGL 3.3)
add_executable(${EXECUTABLE_NAME} src/window.cpp)
add_subdirectory(dependencies/glad)
target_link_libraries(${EXECUTABLE_NAME} glad)
add_subdirectory("${CMAKE_SOURCE_DIR}/dependencies/glfw")
target_link_libraries(${EXECUTABLE_NAME} glfw)

cmake_minimum_required(VERSION 3.15)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Assimp (from your custom install or system)
find_package(assimp REQUIRED)

# Gather source files
file(GLOB_RECURSE SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.c
)

# Executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Include paths (local dependencies)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/dependencies/include   # glad, stb, GLFW headers
    ${CMAKE_SOURCE_DIR}/src
)

# Link with libraries
target_link_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/dependencies/lib       # where glfw3.lib lives
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw3
    opengl32
    assimp::assimp   # use imported target, cleaner than raw "assimp"
)

project(ostov)

file(GLOB_RECURSE SOURCES 
    "src/*.cpp" 
    "src/*.c"
)

add_library(ostov STATIC ${SOURCES})

# Fetch Dependencies (Modern CMake)
include(FetchContent)

# GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.3.8
)

# GLM (数学库)
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        0.9.9.8
)

# Assimp (模型加载库)
FetchContent_Declare(
    assimp
    GIT_REPOSITORY https://github.com/assimp/assimp.git
    GIT_TAG        v5.2.5
)

# 设置依赖项的编译选项 (放在 MakeAvailable 之前)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(GLM_TEST_ENABLE OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "" FORCE)
set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "" FORCE) # 关键：关闭警告转错误

FetchContent_MakeAvailable(glfw assimp glm)

# khrplatform.h 和 glad.h 没办法通过 FetchContent 获取，
# 因为它们是单独的头文件，且没有独立的库。需要手动下载并包含它们。
# Include Directories
target_include_directories(ostov PUBLIC
    include
)

# Link Libraries
if(WIN32)
    target_link_libraries(ostov PUBLIC 
        glfw
        assimp::assimp
        glm::glm
        opengl32
        user32
        gdi32
        shell32
    )
endif()

target_compile_definitions(ostov PUBLIC
    OSTOV_PLATFORM_WINDOWS
)

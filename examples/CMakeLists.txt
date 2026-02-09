project(examples)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(examples_app ${SOURCES})

target_link_libraries(examples_app PRIVATE ostov)

set_target_properties(examples_app PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/examples")

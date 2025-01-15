cmake_minimum_required(VERSION 3.12)

project(loopadrome VERSION 1.0.0.0 LANGUAGES C)

file(GLOB_RECURSE loopadrome_SOURCES CONFIGURE_DEPENDS "src/*.c")
file(GLOB_RECURSE loopadrome_HEADERS CONFIGURE_DEPENDS "src/*.h")

set(loopadrome_INCLUDE_DIRS "")
foreach(_header_file ${loopadrome_HEADERS})
    get_filename_component(_dir ${_header_file} PATH)
    list(APPEND loopadrome_INCLUDE_DIRS ${_dir})
endforeach()

find_package(glfw3 3.3 REQUIRED)

list(REMOVE_DUPLICATES loopadrome_INCLUDE_DIRS)

add_executable(loopadrome_BINARY ${loopadrome_SOURCES})
set_target_properties(loopadrome_BINARY PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")
set_target_properties(loopadrome_BINARY PROPERTIES OUTPUT_NAME "loopadrome")
target_link_libraries(loopadrome_BINARY glfw)
target_include_directories(loopadrome_BINARY PRIVATE ${loopadrome_INCLUDE_DIRS})


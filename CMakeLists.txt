cmake_minimum_required(VERSION 3.13)

project(small-kv C CXX)

# For vscode intellisense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(protobuf_BUILD_TESTS OFF CACHE BOOL "")
add_subdirectory(third_party/protobuf/cmake)
find_package(Protobuf)

add_subdirectory(third_party/rax)
add_subdirectory(proto_types)
add_subdirectory(small-kv)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)

target_link_options(${CMAKE_PROJECT_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-static-libgcc>
    $<$<CXX_COMPILER_ID:GNU>:-static-libstdc++>
    $<$<CXX_COMPILER_ID:GNU>:$<$<PLATFORM_ID:Windows>:-static>>
)

target_link_libraries(${CMAKE_PROJECT_NAME}
    PRIVATE
        small_kv
        proto_types
)

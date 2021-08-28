cmake_minimum_required(VERSION 3.5)

project(small-kv)

set(CMAKE_CXX_STANDARD 11)
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

target_link_libraries(${CMAKE_PROJECT_NAME}
    PRIVATE
        small_kv
        proto_types
)

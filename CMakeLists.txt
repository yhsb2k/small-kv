cmake_minimum_required(VERSION 3.5)

project(small-kv)

set(CMAKE_CXX_STANDARD 11)
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(PROTOBUF_LIBRARY libprotobuf-lite)
set(PROTOBUF_INCLUDE_DIR src/third_party/protobuf/src)
set(protobuf_BUILD_TESTS OFF CACHE BOOL "")
find_package(Protobuf REQUIRED)
set(PROTOBUF_PROTOC_EXECUTABLE protoc)

include_directories(src)
include_directories(src/third_party/protobuf/src)

add_subdirectory(src/third_party/protobuf/cmake)
add_subdirectory(src/proto_types)
add_subdirectory(third_party/rax)
add_subdirectory(src/small-kv)

add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME}
    PRIVATE
        small_kv
        rax
        proto_types
        ${PROTOBUF_LIBRARY}
)
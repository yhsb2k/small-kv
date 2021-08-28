
include_directories(../)
include_directories(../third_party/protobuf/src)

add_library(small_kv
    kv.cpp
)

target_link_libraries(small_kv
    PRIVATE
        rax
)

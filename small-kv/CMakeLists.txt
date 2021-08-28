
add_library(small_kv
    kv.cpp
)

target_link_libraries(small_kv
    PRIVATE
        rax
        protobuf::libprotobuf-lite
)

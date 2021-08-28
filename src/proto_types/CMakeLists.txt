add_library(proto_types
    types.proto
)

protobuf_generate(TARGET proto_types)

target_include_directories(proto_types
    PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(proto_types
    PUBLIC
        protobuf::libprotobuf-lite
)

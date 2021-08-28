#include "kv.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <google/protobuf/stubs/common.h>
extern "C" {
#include "rax.h"
};

using namespace database;

kv::kv()
{
    /* Verify that the version of the library that we linked against is
    compatible with the version of the headers we compiled against. */
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    
    rt = (rax *)raxNew();
}

kv::~kv()
{
    raxFreeWithCallback((rax *)rt, free);
}

int kv::_set(const char *key, uint8_t *buff, size_t size, bool can_create)
{
    // Keep data in memory (radix tree)
    size_t key_len = strlen(key);
    void *node_data = raxFind((rax *)rt, (unsigned char *)key, key_len);
    if(node_data == raxNotFound && !can_create)
        return -1; // Node not found and we can't create new one
    
    uint8_t *new_data = (uint8_t *)malloc(size + sizeof(size));
    if(!new_data)
        return -1;
    memcpy(new_data, &size, sizeof(size));
    memcpy(new_data + sizeof(size), buff, size);
    
    node_data = NULL;
    if(!raxInsert((rax *)rt, (unsigned char *)key, key_len, new_data, &node_data) &&
        errno == ENOMEM)
    {
        free(new_data);
        return -1; // Out of memory error
    }
    
    if(node_data)
        free(node_data);
    
    return 0;
    
    /* Storage implementation using filesystem
    FILE *f = fopen(key, can_create ? "w" : "r+");
    if(!f)
        return -1;
    
    if(fwrite(&size, 1, sizeof(size), f) != sizeof(size))
    {
        fclose(f);
        return -1;
    }
    
    size_t write_size = fwrite(buff, 1, size, f);
    fclose(f);
    
    if(write_size != size)
        return -1;
    
    return 0;*/
}

int kv::_get(const char *key, uint8_t **buff, size_t &size)
{
    // Get data from memory (radix tree)
    uint8_t *node_data = (uint8_t *)raxFind((rax *)rt, (unsigned char *)key, strlen(key));
    if(node_data == raxNotFound)
        return -1;
    
    size = ((size_t *)node_data)[0];
    
    if(!(*buff = (uint8_t *)malloc(size)))
        return -1;
    
    memcpy(*buff, node_data + sizeof(size), size);
    return 0;
    
    /* Storage implementation using filesystem
    FILE *f = fopen(key, "r");
    if(!f)
        return -1;
    
    size_t read_size = fread(&size, 1, sizeof(size), f);
    if(read_size != sizeof(size))
    {
        fclose(f);
        return -1;
    }
    
    if(!(*buff = (uint8_t *)malloc(size)))
    {
        fclose(f);
        return -1;
    }
    
    read_size = fread(*buff, 1, size, f);
    fclose(f);
    
    if(read_size != size)
    {
        free(*buff);
        return -1;
    }
    
    return 0;*/
}
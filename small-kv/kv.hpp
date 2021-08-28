#pragma once

#include <stdint.h>
#include <stdlib.h>

namespace database
{
class kv
{
    public:
        kv();
        ~kv();
        
        template<typename T>
        int set(const char *key, const T &value, bool can_create = false)
        {
            size_t size = value.ByteSizeLong();
            uint8_t buff[size];
            
            if(!value.SerializeToArray(buff, size))
                return -1;
            
            return _set(key, buff, size, can_create);
        }
        
        template<typename T>
        int get(const char *key, T &value)
        {
            uint8_t *buff;
            size_t size;
            int res = _get(key, &buff, size);
            if(res) return res;
            
            res = value.ParseFromArray(buff, size);
            free(buff);
            return res ? 0 : -1;
        }
        
    private:
        int _set(const char *key, uint8_t *buff, size_t size, bool can_create);
        
        // Do not forget to free(buff) after use
        int _get(const char *key, uint8_t **buff, size_t &size);
        
        void *rt;
};
};
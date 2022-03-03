#pragma once

#include <stdint.h>

namespace Ion
{
    struct PythonHeapChunck
    {
        bool used;
        uint8_t size;
        struct PythonHeapChunck *next;
        struct PythonHeapChunck *previous;
    }__attribute__((packed));
    class PythonHeapManager
    {
    public:
        void init();
        void *alloc(size_t size);
        void free(void *address);
    private:
        bool isUsable; // Only when Python has been run
        struct PythonHeapChunck *first;
    };
};
#include <ion.h>
#include <apps/global_preferences.h>
#include <ion/include/ion/python_heap.h>

namespace Ion
{
    void PythonHeapManager::init() {
        if(GlobalPreferences::sharedGlobalPreferences()->memory_heap_available_start == NULL || GlobalPreferences::sharedGlobalPreferences()->memory_heap_available_end == NULL) this->isUsable = false;
        else {
            this->isUsable = true;
            this->first = (struct PythonHeapChunck*)GlobalPreferences::sharedGlobalPreferences()->memory_heap_available_start;
            this->first->size = GlobalPreferences::sharedGlobalPreferences()->memory_heap_available_end - GlobalPreferences::sharedGlobalPreferences()->memory_heap_available_start;
            this->first->size -= sizeof(struct PythonHeapChunck);
            this->first->used = false;
            this->first->next = NULL;
            this->first->previous = NULL;
        }
    }

    void *PythonHeapManager::alloc(size_t size) {
        if(!this->isUsable) return NULL;

        struct PythonHeapChunck *result = NULL;
        for(struct PythonHeapChunck *chunck = this->first; chunck != NULL; chunck = chunck->next) {
            if(chunck->size >= size + sizeof(struct PythonHeapChunck) + 1 && !chunck->used) {
                result = chunck;
                break;
            }
        }

        if(!result) return NULL;

        result->used = true;
        struct PythonHeapChunck *next = (struct PythonHeapChunck*)((uint32_t*)result + sizeof(struct PythonHeapChunck) + size);
        next->used = false;
        next->previous = result;
        next->next = result->next;
        next->size = result->size - size - sizeof(struct PythonHeapChunck);
        result->size = size;
        result->next = next;
        return (void*)((uint32_t*)(result + sizeof(struct PythonHeapChunck)));
    }

    void PythonHeapManager::free(void *address) {
        if(!this->isUsable) return;
        
        struct PythonHeapChunck *to_remove = (struct PythonHeapChunck*)(address - sizeof(struct PythonHeapChunck));
        to_remove->used = false;
        
        // If the previous chunck is not used
        if(to_remove->previous && !to_remove->previous->used) {
            to_remove->previous->next = to_remove->next;
            to_remove->previous->size += sizeof(struct PythonHeapChunck) + to_remove->size;
        }
        // If the next chunck is free
        if(to_remove->next && !to_remove->next->used) {
            to_remove->next->previous = to_remove->previous;
            to_remove->size += sizeof(struct PythonHeapChunck) + to_remove->size;
        }
    }
};
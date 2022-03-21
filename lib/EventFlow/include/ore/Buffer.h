#pragma once

#include <ore/Allocator.h>
#include <ore/Types.h>

namespace ore {

struct Buffer {
    template <typename T>
    void Allocate(Allocator* allocator, int num) {
        size = sizeof(T) * num;
        data = static_cast<char*>(allocator->New(size));
    }

    void Free(Allocator* allocator) {
        allocator->Free(data);
        data = nullptr;
        size = 0;
    }

    char* data;
    int size;
};

}  // namespace ore

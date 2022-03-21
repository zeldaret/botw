#pragma once

#include <cstddef>

namespace nv {
void SetGraphicsAllocator(void* (*allocator)(size_t, size_t, void*),
                          void (*deallocator)(void*, void*),
                          void* (*reallocator)(void*, size_t, void*), void* unk);
void SetGraphicsDevtoolsAllocator(void* (*allocator)(size_t, size_t, void*),
                                  void (*deallocator)(void*, void*),
                                  void* (*reallocator)(void*, size_t, void*), void* unk);
void InitializeGraphics(void* address, size_t size);
}  // namespace nv

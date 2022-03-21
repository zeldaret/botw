#include <cafe.h>

#include <heap/seadArena.h>

namespace sead
{
Arena::Arena() : mStart(NULL), mSize(0) {}

Arena::~Arena() {}

u8* Arena::initialize(size_t size)
{
    MEMHeapHandle handle = MEMGetBaseHeapHandle(MEM_ARENA_2);
    u32 allocSize = MEMGetAllocatableSizeForExpHeap(handle);
    if (size > allocSize)
        size = allocSize;

    mSize = size;
    mStart = static_cast<u8*>((*MEMAllocFromDefaultHeapEx)(size, MEM_HEAP_DEFAULT_ALIGNMENT));

    return mStart;
}

}  // namespace sead

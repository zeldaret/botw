#pragma once

#include <basis/seadTypes.h>
#include <heap/seadExpHeap.h>
#include <heap/seadHeap.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::util {

class DualHeap : public sead::ExpHeap {
    SEAD_RTTI_OVERRIDE(DualHeap, sead::ExpHeap)

public:
    static DualHeap* tryCreate(size_t size, const sead::SafeString& name, Heap* parent1,
                               Heap* parent2, s32 alignment, HeapDirection direction, bool b);
    static DualHeap* create(size_t size, const sead::SafeString& name, Heap* parent1, Heap* parent2,
                            s32 alignment, HeapDirection direction, bool b);

    void* tryAlloc(size_t size, s32 alignment, bool* ok);

    void* tryAlloc(size_t size, s32 alignment) override;
    void free(void* ptr) override;
    void* resizeFront(void* p_void, size_t size) override;
    void* resizeBack(void* p_void, size_t size) override;
    void* tryRealloc(void* ptr, size_t size, s32 alignment) override;
    void freeAll() override;
    size_t getFreeSize() const override;
    size_t getMaxAllocatableSize(int alignment) const override;
    bool isResizable() const override;
    bool isAdjustable() const override;
    void dumpYAML(sead::WriteStream& stream, int i) const override;
    void genInformation_(sead::hostio::Context* context) override;
    void makeMetaString_(sead::BufferedSafeString* string) override;

protected:
    DualHeap(size_t size, const sead::SafeString& name, Heap* parent1, Heap* parent2, s32 alignment,
             HeapDirection direction, bool b);
    ~DualHeap() override;

    sead::Heap* mHeap;
    void* _118;
    u8 _120;
    void* _128;
};
KSYS_CHECK_SIZE_NX150(DualHeap, 0x130);

/// Returns the specified heap if it is not null. Otherwise, this returns the current heap.
sead::Heap* getHeapOrCurrentHeap(sead::Heap* heap);

void adjustHeapOrCurrentHeap(sead::Heap* heap);

sead::Heap* getCurrentHeap();
sead::Heap* getDebugHeap();
sead::Heap* getDebugHeap2();

}  // namespace ksys::util

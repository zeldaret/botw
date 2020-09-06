#pragma once

#include <basis/seadTypes.h>
#include <heap/seadExpHeap.h>
#include <heap/seadFrameHeap.h>
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
KSYS_CHECK_SIZE_NX150(sead::ExpHeap, 0x110);
KSYS_CHECK_SIZE_NX150(DualHeap, 0x130);

class DualFrameHeap : public sead::FrameHeap {
    SEAD_RTTI_OVERRIDE(DualFrameHeap, sead::FrameHeap)

public:
    static DualFrameHeap* tryCreate(size_t size, const sead::SafeString& name, Heap* parent1,
                                    Heap* parent2, s32 alignment, HeapDirection direction, bool b);
    static DualFrameHeap* create(size_t size, const sead::SafeString& name, Heap* parent1,
                                 Heap* parent2, s32 alignment, HeapDirection direction, bool b);

    size_t adjust() override;
    void* tryAlloc(size_t size, s32 alignment) override;
    void free(void* ptr) override;
    size_t getFreeSize() const override;
    size_t getMaxAllocatableSize(int alignment) const override;
    bool isInclude(const void* p_void) const override;
    bool isEmpty() const override;
    bool isAdjustable() const override;
    void genInformation_(sead::hostio::Context* context) override;
    void makeMetaString_(sead::BufferedSafeString* string) override;

protected:
    DualFrameHeap(size_t size, const sead::SafeString& name, Heap* parent1, Heap* parent2,
                  s32 alignment, HeapDirection direction, bool b);
    ~DualFrameHeap() override;

    sead::Heap* mHeap2;
    void* _f8;
    u8 _100;
};
KSYS_CHECK_SIZE_NX150(sead::FrameHeap, 0xf0);
KSYS_CHECK_SIZE_NX150(DualFrameHeap, 0x108);

sead::Heap* tryCreateDualHeap(size_t size, const sead::SafeString& name, sead::Heap* heap1,
                              sead::Heap* heap2, sead::Heap::HeapDirection direction);

/// Same as tryCreateDualHeap, but asserts on failure.
sead::Heap* createDualHeap(size_t size, const sead::SafeString& name, sead::Heap* heap1,
                           sead::Heap* heap2, sead::Heap::HeapDirection direction);

/// Returns the specified heap if it is not null. Otherwise, this returns the current heap.
sead::Heap* getHeapOrCurrentHeap(sead::Heap* heap);

void adjustHeapOrCurrentHeap(sead::Heap* heap);

sead::Heap* getCurrentHeap();
sead::Heap* getDebugHeap();
sead::Heap* getDebugHeap2();

}  // namespace ksys::util

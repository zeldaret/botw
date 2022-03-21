#pragma once

#include "heap/seadHeap.h"

namespace sead
{
class FrameHeap : public Heap
{
    SEAD_RTTI_OVERRIDE(FrameHeap, Heap)
public:
    struct State
    {
        void* mHeadPtr;
        void* mTailPtr;
    };

    static FrameHeap* tryCreate(size_t size, const SafeString& name, Heap* parent, s32,
                                HeapDirection direction, bool);
    static FrameHeap* create(size_t size, const SafeString& name, Heap* parent, s32,
                             HeapDirection direction, bool);

    static size_t getManagementAreaSize(s32);

    void restoreState(const State& state);
    void freeHead();
    void freeTail();

    void destroy() override;
    size_t adjust() override;
    void* tryAlloc(size_t size, s32 alignment) override;
    void free(void* ptr) override;
    void* resizeFront(void* p_void, size_t size) override;
    void* resizeBack(void* p_void, size_t size) override;
    void freeAll() override;
    uintptr_t getStartAddress() const override;
    uintptr_t getEndAddress() const override;
    size_t getSize() const override;
    size_t getFreeSize() const override;
    size_t getMaxAllocatableSize(int alignment) const override;
    bool isInclude(const void* p_void) const override;
    bool isEmpty() const override;
    bool isFreeable() const override;
    bool isResizable() const override;
    bool isAdjustable() const override;
    void dump() const override;
    void dumpYAML(WriteStream& stream, int i) const override;
    void genInformation_(hostio::Context* context) override;

protected:
    FrameHeap(const SafeString& name, Heap* parent, void* address, size_t size,
              HeapDirection direction, bool);
    ~FrameHeap() override;

    void initialize_();
    void* getAreaStart_() const;
    void* getAreaEnd_() const;

    State mState;
};
}  // namespace sead

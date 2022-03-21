#ifndef SEAD_HEAPMGR_H_
#define SEAD_HEAPMGR_H_

#include <container/seadPtrArray.h>
#include <heap/seadArena.h>
#include <heap/seadHeap.h>
#include <thread/seadAtomic.h>
#include <thread/seadCriticalSection.h>

namespace sead
{
class HeapMgr
{
public:
    HeapMgr();
    virtual ~HeapMgr() {}

    Heap* getCurrentHeap();
    Heap* findContainHeap(const void* ptr) const;
    static bool isContainedInAnyHeap(const void* ptr);

    static HeapMgr* instance() { return sInstancePtr; }
    static s32 getRootHeapNum() { return sRootHeaps.size(); }

    // TODO: these should be private
    static HeapMgr sInstance;
    static HeapMgr* sInstancePtr;

    using RootHeaps = FixedPtrArray<Heap, 4>;
    using IndependentHeaps = FixedPtrArray<Heap, 4>;

private:
    friend class ScopedCurrentHeapSetter;

    /// Set the current heap to the specified heap and returns the previous "current heap".
    sead::Heap* setCurrentHeap_(sead::Heap* heap);

    static Arena sDefaultArena;
    static RootHeaps sRootHeaps;
    static IndependentHeaps sIndependentHeaps;
    static CriticalSection sHeapTreeLockCS;

    void*
        mAllocFailedCallback;  // IAllocFailedCallback* = IDelegate1<const AllocFailedCallbackArg*>*
};

/// Sets the "current heap" to the specified heap and restores the previous "current heap"
/// when this goes out of scope.
class ScopedCurrentHeapSetter
{
public:
    explicit ScopedCurrentHeapSetter(sead::Heap* heap)
    {
        if (heap)
            setPreviousHeap_(HeapMgr::instance()->setCurrentHeap_(heap));
        else
            setPreviousHeapToNone_();
    }

    ~ScopedCurrentHeapSetter()
    {
        if (hasPreviousHeap_())
            HeapMgr::instance()->setCurrentHeap_(getPreviousHeap_());
    }

protected:
    /// @warning Only call this if hasPreviousHeap returns true.
    Heap* getPreviousHeap_() const { return reinterpret_cast<Heap*>(mPreviousHeap); }
    void setPreviousHeap_(Heap* heap) { mPreviousHeap = reinterpret_cast<uintptr_t>(heap); }
    void setPreviousHeapToNone_() { mPreviousHeap = 1; }
    bool hasPreviousHeap_() const
    {
        // XXX: We cannot just do `mPreviousHeap != 1` because that results in different codegen.
        // The cast smells like implementation defined behavior, but 1 should not be a valid
        // pointer on any platform that we support. In practice, this will work correctly.
        return reinterpret_cast<Heap*>(mPreviousHeap) != reinterpret_cast<Heap*>(1);
    }

    uintptr_t mPreviousHeap;
};

class FindContainHeapCache
{
public:
    FindContainHeapCache();

    bool tryRemoveHeap(Heap* heap);
    // getHeap and setHeap probably exist too

    Atomic<uintptr_t> mHeap;
};

}  // namespace sead

#endif  // SEAD_HEAPMGR_H_

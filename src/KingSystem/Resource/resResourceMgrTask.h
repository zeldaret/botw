#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadListImpl.h>
#include <container/seadObjArray.h>
#include <container/seadOffsetList.h>
#include <container/seadPtrArray.h>
#include <filedevice/seadArchiveFileDevice.h>
#include <framework/seadCalculateTask.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadDelegate.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadAtomic.h>
#include <thread/seadCriticalSection.h>
#include <thread/seadDelegateThread.h>
#include <thread/seadReadWriteLock.h>
#include <time/seadTickTime.h>
#include "KingSystem/Resource/resControlTask.h"
#include "KingSystem/Resource/resCounter.h"
#include "KingSystem/Resource/resInfoContainer.h"
#include "KingSystem/Resource/resUnit.h"
#include "KingSystem/Resource/resUnitPool.h"
#include "KingSystem/System/OverlayArena.h"

namespace sead {
class Heap;
}

namespace ksys {
class OverlayArena;

namespace util {
class TaskMgr;
class TaskPostRunResult;
class TaskThread;
}  // namespace util
}  // namespace ksys

namespace ksys::res {

class Cache;
class CompactedHeap;
class ControlTaskData;
class EntryFactoryBase;
class MemoryTaskData;
class OffsetReadFileDevice;
class TextureHandleList;
class TextureHandleMgr;

class FileDevicePrefix {
public:
    FileDevicePrefix() = default;

    sead::FileDevice* getFileDevice() { return mFileDevice; }
    void setFileDevice(sead::FileDevice* device) { mFileDevice = device; }

    const sead::SafeString& getPrefix() { return mPrefix; }
    void setPrefix(const sead::SafeString& prefix) { mPrefix = prefix; }

    static constexpr size_t getListNodeOffset() { return offsetof(FileDevicePrefix, mListNode); }

private:
    sead::ListNode mListNode;
    sead::FileDevice* mFileDevice = nullptr;
    sead::SafeString mPrefix;
};
KSYS_CHECK_SIZE_NX150(FileDevicePrefix, 0x28);

// FIXME: very, very incomplete.
class ResourceMgrTask : public sead::CalculateTask, public sead::hostio::Node {
    SEAD_RTTI_OVERRIDE(ResourceMgrTask, sead::CalculateTask)
public:
    static ResourceMgrTask* instance() { return sInstance; }

    void prepare() override;

    void insertOverlayArena(OverlayArena* arena);
    OverlayArena* getSomeArena() const;

    util::TaskThread* makeResourceLoadingThread(sead::Heap* heap, bool use_game_task_thread);

    struct GetUnitArg {
        const ResourceUnit::InitArg* unit_init_arg;
        OverlayArena* arena;
    };
    ResourceUnit* clearCachesAndGetUnit(const GetUnitArg& arg);

    void eraseUnit(ResourceUnit* unit);

    struct ClearCacheArg {
        ResourceUnit* unit;
    };
    void clearCache(ClearCacheArg& arg, void* x = nullptr);

    bool dropSFromExtensionIfNeeded(const sead::SafeString& path,
                                    sead::BufferedSafeString& new_path, s32 dot_idx,
                                    const sead::SafeString& extension);

private:
    enum class Flag {

    };

    using ResourceUnitDelegate = sead::Delegate1RFunc<void*, bool>;
    using TaskCallback =
        sead::Delegate2Func<util::TaskPostRunResult*, const util::TaskPostRunContext&>;
    using MemoryTaskDelegate = sead::Delegate1R<ResourceMgrTask, void*, bool>;

    struct ResourceUnitDelegatePair {
        ResourceUnitDelegate fn;
        TaskCallback cb;
    };

    explicit ResourceMgrTask(const sead::TaskConstructArg& arg);
    ~ResourceMgrTask();

    bool callSystemCalc_(void* userdata);
    static void setInstance(ResourceMgrTask* task);

    static ResourceMgrTask* sInstance;

    struct InstancePtrClearer {
        ~InstancePtrClearer() {
            if (mClearOnDestruction)
                ResourceMgrTask::sInstance = nullptr;
        }

        bool mClearOnDestruction = false;
    };
    InstancePtrClearer mInstancePtrClearer;

    sead::TypedBitFlag<Flag> mFlags;
    bool mClearAllCachesRequested = false;
    u32 _17c = 0;
    sead::Heap* mResSystemHeap = nullptr;
    util::TaskThread* mResourceLoadingThread = nullptr;
    util::TaskThread* mResourceControlThread = nullptr;
    util::TaskThread* mResourceMemoryThread = nullptr;
    util::TaskThread* mMovableMemoryThread = nullptr;
    sead::PtrArray<util::TaskThread>* mActorCreateInitializerThreads = nullptr;
    util::TaskMgr* mResourceControlTaskMgr = nullptr;
    util::TaskMgr* mResourceMemoryTaskMgr;
    ControlTask* mControlTask = nullptr;
    util::Task* mTask1 = nullptr;
    util::Task* mTask2 = nullptr;
    util::Task* mTask3 = nullptr;

    EntryFactoryBase* mEntryFactoryBase = nullptr;
    EntryFactoryBase* mDefaultEntryFactory = nullptr;

    sead::Buffer<Cache> mCaches;
    sead::FixedObjArray<s32, 4> mThreadIds;
    u8* mOffsetReadBuf = nullptr;
    sead::CriticalSection mSzsDecompressorCS;
    sead::CriticalSection mFactoryCS;

    ResourceUnitDelegatePair mUnitInitLoadFn;
    ResourceUnitDelegate mUnitPrepareLoadFn;
    ResourceUnitDelegate mUnitAdjustHeapFn;
    ResourceUnitDelegatePair mDelegate2;  // TODO: rename
    ResourceUnitDelegatePair mUnitUnloadFn;
    ResourceUnitDelegatePair mUnitClearCacheForSyncFn;
    ResourceUnitDelegatePair mUnitClearCacheFn;

    MemoryTaskDelegate mClearAllCachesFn;
    MemoryTaskDelegate mClearCachesFn;
    MemoryTaskDelegate mDefragAllMemoryMgrFn;

    MemoryTaskDelegate mLoadFn;
    sead::Delegate2<ResourceMgrTask, util::TaskPostRunResult*, const util::TaskPostRunContext&>
        mLoadCb;
    sead::Delegate1<ResourceMgrTask, const util::TaskRemoveCallbackContext&> mLoadTaskRemoveCb;

    MemoryTaskDelegate mCalcFn;
    MemoryTaskDelegate mCalcArenaHeapSizeFn;
    ResourceUnitDelegate mUnitDelegate17;  // TODO: rename
    ResourceUnitDelegate mUnitDeleteFn;

    s32 _4c8 = -1;
    u32 _4cc = 0;

    ResourceUnitPool mUnitPool;
    sead::CriticalSection mCritSection;
    sead::OffsetList<ResourceUnit> mUnits;
    sead::OffsetList<bool> mSomeList;  // TODO: fix the type and rename

    sead::FileDevice* mSeadMainFileDevice = nullptr;
    OffsetReadFileDevice* mOffsetReadFileDevice = nullptr;
    Handle* mPackHandle = nullptr;
    sead::ArchiveFileDevice mArchiveFileDev1{nullptr};  // TODO: rename
    sead::ArchiveFileDevice mArchiveFileDev2{nullptr};  // TODO: rename
    sead::ArchiveFileDevice mArchiveFileDev3{nullptr};  // TODO: rename
    sead::CriticalSection mCritSection2;                // TODO: rename

    u32 _9c08d0 = 0;
    sead::ObjArray<sead::SafeString> mExtensions1;  // TODO: rename
    sead::ObjArray<sead::SafeString> mExtensions2;  // TODO: rename

    sead::OffsetList<OverlayArena> mArenas;
    sead::CriticalSection mArenasCS;

    OverlayArena mArenaForResourceS;
    OverlayArena mArenaForResourceL;

    ResourceInfoContainer mResourceInfoContainer;

    sead::OffsetList<FileDevicePrefix> mFileDevicePrefixes;
    sead::ReadWriteLock mFileDevicePrefixesLock;

    TextureHandleMgr* mTexHandleMgr = nullptr;
    TextureHandleList* mTexHandleList = nullptr;
    sead::CriticalSection mCritSection3;  // TODO: rename

    sead::Heap* mCompactedHeapMainSeadHeap = nullptr;
    u8* mCompactedHeapMainBuffer = nullptr;
    CompactedHeap* mCompactedHeapMain = nullptr;
    u8* mCompactedHeapMip0Buffer = nullptr;
    CompactedHeap* mCompactedHeapMip0 = nullptr;
    u8* mCompactedHeapMainBuffer2 = nullptr;
    sead::Atomic<u32> mCompactionStopped = 0;
    sead::Atomic<u32> _9c0d3c = 0;
    sead::Atomic<u32> _9c0d40 = 0;
    sead::AnyDelegate2<sead::Thread*, sead::MessageQueue::Element> mCompactionThreadFn;
    sead::DelegateThread* mCompactionThread = nullptr;
    Counter mCounter;

    u32 _9c0d88 = 1;
    u32 _9c0d8c = 0;
    u32 _9c0d90 = 0;
    u32 _9c0d94;
    u8 _9c0d98 = 1;
    size_t _9c0da0 = 500;

    util::Task mTask;                     // TODO: rename
    sead::CriticalSection mCritSection4;  // TODO: rename
    sead::TickTime mTickTime;
    MemoryTaskDelegate mSystemCalcFn;
};
KSYS_CHECK_SIZE_NX150(sead::TaskBase, 0xd0);
KSYS_CHECK_SIZE_NX150(sead::MethodTreeNode, 0x98);
KSYS_CHECK_SIZE_NX150(ResourceMgrTask, 0x9c0eb8);

}  // namespace ksys::res

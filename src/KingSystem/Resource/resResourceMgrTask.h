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
#include <prim/seadSafeString.h>
#include <prim/seadStringBuilder.h>
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
class Resource;
class SZSDecompressor;
}  // namespace sead

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

    sead::FileDevice* getFileDevice() const { return mFileDevice; }
    void setFileDevice(sead::FileDevice* device) { mFileDevice = device; }

    const sead::SafeString& getPrefix() const { return mPrefix; }
    void setPrefix(const sead::SafeString& prefix) { mPrefix = prefix; }

    bool getField28() const { return _28; }
    void setField28(bool value) { _28 = value; }

    static constexpr size_t getListNodeOffset() { return offsetof(FileDevicePrefix, mListNode); }

private:
    sead::ListNode mListNode;
    sead::FileDevice* mFileDevice = nullptr;
    sead::SafeString mPrefix;
    bool _28 = false;
};
KSYS_CHECK_SIZE_NX150(FileDevicePrefix, 0x30);

// FIXME: very incomplete.
class ResourceMgrTask : public sead::CalculateTask, public sead::hostio::Node {
    SEAD_RTTI_OVERRIDE(ResourceMgrTask, sead::CalculateTask)
public:
    enum class LaneId {
        _0 = 0,
        _1 = 1,
        _2 = 2,
        _3 = 3,
        _4 = 4,
        _5 = 5,
        _6 = 6,
        _7 = 7,
        _8 = 8,
        _9 = 9,
        _10 = 10,
    };

    using ResourceUnitDelegate = sead::Delegate1RFunc<void*, bool>;
    using TaskCallback =
        sead::Delegate2Func<util::TaskPostRunResult*, const util::TaskPostRunContext&>;
    using MemoryTaskDelegate = sead::Delegate1R<ResourceMgrTask, void*, bool>;

    struct ResourceUnitDelegatePair {
        ResourceUnitDelegate fn;
        TaskCallback cb;
    };

    static ResourceMgrTask* instance() { return sInstance; }

    void prepare() override;

    void insertOverlayArena(OverlayArena* arena);

    util::TaskThread* makeResourceLoadingThread(sead::Heap* heap, bool use_game_task_thread);

    void clearAllCaches(OverlayArena* arena);
    OverlayArena* getTexHandleMgrArena() const;

    void requestDefragAllMemoryMgr();
    bool isDefragDone() const;
    f32 getDefragProgress() const;

    s32 getCacheIdx(const sead::SafeString& path) const;

    void cancelTasks();
    void waitForTaskQueuesToEmpty();
    s32 getNumActiveTasksOnResLoadingThread() const;

    OffsetReadFileDevice* getOffsetReadFileDevice() const;
    sead::ArchiveFileDevice* getArchiveFileDev1();

    void controlField9c0d88(bool off);
    void setFlag2000Or5000(s32 type);

    void copyLoadRequest(ILoadRequest* request, const sead::SafeString& path,
                         const ILoadRequest& source_request);

    EntryFactoryBase* getFactoryForPath(const sead::SafeString& path) const;

    bool isFlag4Set() const;

    s32 requestLoad(Handle* handle, const sead::SafeString& path, const ILoadRequest& request);
    void addSExtensionPrefix(sead::StringBuilder& builder) const;
    s32 requestLoadForSync(Handle* handle, const sead::SafeString& path,
                           const ILoadRequest& request);
    s32 requestUnload(Handle* handle, const sead::SafeString& path, const ILoadRequest& request);

    void registerUnit(ResourceUnit* unit);
    void deregisterUnit(ResourceUnit* unit);

    void requestClearCache(ResourceUnit** p_unit, util::Task* task = nullptr);
    void requestClearCacheForSync(ResourceUnit** p_unit, bool clear_immediately,
                                  bool delete_immediately);

    void deleteUnit(ResourceUnit*& unit, bool sync);
    void requestDeleteUnit(ResourceUnit** p_unit);

    struct DirectLoadArg {
        LoadRequest req;
        sead::Heap* heap;
    };
    sead::DirectResource* load(const DirectLoadArg& arg);

    bool canUseSdCard() const;
    bool returnFalse() const;

    bool dropSFromExtensionIfNeeded(const sead::SafeString& path,
                                    sead::BufferedSafeString& new_path, s32 dot_idx,
                                    const sead::SafeString& extension) const;

    void unloadSeadResource(sead::Resource* resource);

    u32 getResourceSize(const sead::SafeString& name, sead::FileDevice* file_device) const;

    void registerFileDevicePrefix(FileDevicePrefix& prefix);
    void deregisterFileDevicePrefix(FileDevicePrefix& prefix);

    void callStubbedFunctionOnArenas();
    void updateResourceArenasFlag8();

    struct MakeHeapArg {
        bool _0 = false;
        u32 heap_size = 0;
        ResourceUnit* unit = nullptr;
        sead::SafeString path;
        OverlayArena* arena = nullptr;
        OverlayArena** out_arena1 = nullptr;
        OverlayArena** out_arena2 = nullptr;
    };
    KSYS_CHECK_SIZE_NX150(MakeHeapArg, 0x38);
    sead::Heap* makeHeapForUnit(const MakeHeapArg& arg);

    struct GetUnitArg {
        const ResourceUnit::InitArg* unit_init_arg;
        OverlayArena* arena;
    };
    ResourceUnit* clearCachesAndGetUnit(const GetUnitArg& arg);

    struct SetActorCreateInitializerThreadsArg {
        sead::PtrArray<util::TaskThread>* threads;
    };
    void setActorCreateInitializerThreads(const SetActorCreateInitializerThreadsArg& arg);
    void clearActorCreateInitializerThreads();

    void pauseThreads();
    void resumeThreads();

    sead::SZSDecompressor* getSzsDecompressor();
    void unlockSzsDecompressorCS();
    bool getUncompressedSize(u32* size, const sead::SafeString& path,
                             sead::FileDevice* device) const;

    void setCompactionStopped(bool stopped);
    bool isCompactionStopped() const;

    bool returnTrue1();

    void clearCacheWithFileExtension(const sead::SafeString& extension);
    void clearAllCachesSynchronously(OverlayArena* arena);

    bool returnTrue();

    struct ResourceSizeInfo {
        bool is_archive_file_dev2;
        u32 buffer_size;
        u32 alloc_size;
        sead::FileDevice* file_device;
    };
    KSYS_CHECK_SIZE_NX150(ResourceSizeInfo, 0x18);

    struct GetResourceSizeInfoArg {
        bool flag1;
        bool flag4_try_decomp;
        bool flag2;
        u32 alloc_size;
        sead::ArchiveRes* archive_res;
        sead::FileDevice* file_device;
        EntryFactoryBase* factory;
        u32 load_data_alignment;
        sead::SafeString str;  // TODO: rename
        sead::SafeString path;
    };
    KSYS_CHECK_SIZE_NX150(GetResourceSizeInfoArg, 0x48);

    void getResourceSizeInfo(ResourceSizeInfo* info, const GetResourceSizeInfoArg& arg);

    void removeOverlayArena(OverlayArena* arena);

    util::TaskThread* getResourceLoadingThread() const { return mResourceLoadingThread; }
    util::TaskThread* getResourceControlThread() const { return mResourceControlThread; }
    util::TaskThread* getResourceMemoryThread() const { return mResourceMemoryThread; }
    util::TaskThread* getMovableMemoryThread() const { return mMovableMemoryThread; }

    ResourceUnitDelegatePair& getUnitInitLoadFn() { return mUnitInitLoadFn; }
    auto& getUnitAdjustHeapFn() { return mUnitAdjustHeapFn; }

private:
    enum class Flag {
        _1 = 1,
        _2 = 2,
        _4 = 4,
        _8 = 8,
        _400 = 0x400,
        _1000 = 0x1000,
        _2000 = 0x2000,
        _4000 = 0x4000,
    };

    enum class CacheControlFlag : u8 {
        ClearAllCachesRequested = 1,
    };

    explicit ResourceMgrTask(const sead::TaskConstructArg& arg);
    ~ResourceMgrTask();

    bool calc_(void* userdata);
    bool callSystemCalc_(void* userdata);
    void clearUnits_();
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
    sead::TypedBitFlag<CacheControlFlag> mCacheControlFlags;
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

    sead::Buffer<Cache*> mCaches;
    sead::FixedObjArray<s32, 4> mThreadIds;
    u8* mOffsetReadBuf = nullptr;
    mutable sead::CriticalSection mSzsDecompressorCS;
    sead::CriticalSection mFactoryCS;

    ResourceUnitDelegatePair mUnitInitLoadFn;
    ResourceUnitDelegate mUnitPrepareLoadFn;
    ResourceUnitDelegate mUnitAdjustHeapFn;
    ResourceUnitDelegatePair mUnitUnloadForSyncFn;
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
    s32 _4cc = 0;

    ResourceUnitPool mUnitPool;
    sead::CriticalSection mUnitsCS;
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
    mutable sead::CriticalSection mArenasCS;

    OverlayArena mArenaForResourceS;
    OverlayArena mArenaForResourceL;

    ResourceInfoContainer mResourceInfoContainer;

    sead::OffsetList<FileDevicePrefix> mFileDevicePrefixes;
    mutable sead::ReadWriteLock mFileDevicePrefixesLock;

    TextureHandleMgr* mTexHandleMgr = nullptr;
    TextureHandleList* mTexHandleList = nullptr;
    sead::CriticalSection mCritSection3;  // TODO: rename

    sead::Heap* mCompactedHeapMainSeadHeap = nullptr;
    u8* mCompactedHeapMainBuffer = nullptr;
    CompactedHeap* mCompactedHeapMain = nullptr;
    u8* mCompactedHeapMip0Buffer = nullptr;
    CompactedHeap* mCompactedHeapMip0 = nullptr;
    u8* mCompactedHeapMainBuffer2 = nullptr;
    sead::Atomic<u32> mCompactionCounter = 0;
    sead::Atomic<u32> _9c0d3c = 0;
    sead::Atomic<u32> _9c0d40 = 0;
    sead::AnyDelegate2<sead::Thread*, sead::MessageQueue::Element> mCompactionThreadFn;
    sead::DelegateThread* mCompactionThread = nullptr;
    Counter mCounter;

    sead::Atomic<s32> _9c0d88 = 1;
    u32 _9c0d8c = 0;
    u32 mArenaIdx = 0;
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

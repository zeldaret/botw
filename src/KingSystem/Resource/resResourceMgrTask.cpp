#include "KingSystem/Resource/resResourceMgrTask.h"
#include <framework/seadHeapPolicies.h>
#include <framework/seadTaskID.h>
#include <thread/seadThreadUtil.h>
#include "KingSystem/Resource/resCompactedHeap.h"
#include "KingSystem/Resource/resEntryFactory.h"
#include "KingSystem/Resource/resSystem.h"
#include "KingSystem/Resource/resTextureHandleList.h"
#include "KingSystem/Resource/resTextureHandleMgr.h"
#include "KingSystem/Utils/SafeDelete.h"
#include "KingSystem/Utils/Thread/GameTaskThread.h"
#include "KingSystem/Utils/Thread/TaskMgr.h"
#include "KingSystem/Utils/Thread/TaskThread.h"

namespace ksys::res {

void ResourceMgrTask::setInstance(ResourceMgrTask* task) {
    if (!sInstance) {
        sInstance = task;
        task->mInstancePtrClearer.mClearOnDestruction = true;
    }
}

ResourceMgrTask::ResourceMgrTask(const sead::TaskConstructArg& arg)
    : sead::CalculateTask(arg, "res::ResourceMgrTask"),
      mSzsDecompressorCS(arg.heap_array->getPrimaryHeap()),
      mCounter(arg.heap_array->getPrimaryHeap()), mTask(arg.heap_array->getPrimaryHeap()) {
    mArenas.initOffset(OverlayArena::getListNodeOffset());
    mUnits.initOffset(ResourceUnit::getResMgrUnitListNodeOffset());
    mSomeList.initOffset(0x188);  // TODO: replace this with a "get offset" call
    mSystemCalcFn.bind(this, &ResourceMgrTask::callSystemCalc_);
    mFileDevicePrefixes.initOffset(FileDevicePrefix::getListNodeOffset());
}

ResourceMgrTask::~ResourceMgrTask() {
    util::safeDelete(mTexHandleList);
    util::safeDelete(mTexHandleMgr);
    util::safeDeleteThread(mCompactionThread);

    if (mCompactedHeapMip0) {
        mCompactedHeapMip0->destroy();
        util::safeDeleteArray(mCompactedHeapMip0Buffer);
    }

    if (mCompactedHeapMain) {
        mCompactedHeapMain->destroy();
        util::safeDeleteArray(mCompactedHeapMainBuffer);
        mCompactedHeapMainSeadHeap->destroy();
    }

    util::safeDeleteArray(mCompactedHeapMainBuffer2);
    util::safeDeleteArray(mOffsetReadBuf);
    mExtensions2.freeBuffer();
    mExtensions1.freeBuffer();

    util::safeDeleteThread(mMovableMemoryThread);
    util::safeDeleteThread(mResourceMemoryThread);
    util::safeDeleteThread(mResourceControlThread);
    util::safeDeleteThread(mResourceLoadingThread);
    util::safeDelete(mTask3);
    util::safeDelete(mTask2);
    util::safeDelete(mTask1);
    util::safeDelete(mControlTask);

    if (mResourceMemoryTaskMgr) {
        mResourceMemoryTaskMgr->finalize();
        util::safeDelete(mResourceMemoryTaskMgr);
    }

    if (mResourceControlTaskMgr) {
        mResourceControlTaskMgr->finalize();
        util::safeDelete(mResourceControlTaskMgr);
    }

    util::safeDelete(mEntryFactoryBase);

    mResSystemHeap->destroy();
}

void ResourceMgrTask::insertOverlayArena(OverlayArena* arena) {
    auto lock = sead::makeScopedLock(mArenasCS);
    if (!mArenas.isNodeLinked(arena)) {
        mArenas.pushBack(arena);
        stubbedLogFunction();
    }
}

util::TaskThread* ResourceMgrTask::makeResourceLoadingThread(sead::Heap* heap,
                                                             bool use_game_task_thread) {
    if (use_game_task_thread) {
        return new (heap) util::GameTaskThread(
            "Resource Loading", heap, sead::ThreadUtil::ConvertPrioritySeadToPlatform(19),
            sead::MessageQueue::BlockType::Blocking, 0x7fffffff, 0xfa000, 32);
    }

    return new (heap) util::TaskThread(
        "Resource Loading", heap, sead::ThreadUtil::ConvertPrioritySeadToPlatform(19),
        sead::MessageQueue::BlockType::Blocking, 0x7fffffff, 0xa000, 32);
}

}  // namespace ksys::res

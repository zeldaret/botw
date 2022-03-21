#include <framework/seadFramework.h>
#include <framework/seadMethodTreeMgr.h>
#include <framework/seadTaskBase.h>
#include <framework/seadTaskMgr.h>
#include <prim/seadSafeString.h>
#include <resource/seadResourceMgr.h>
#include <thread/seadDelegateThread.h>

namespace sead
{
bool TaskMgr::changeTaskState_(TaskBase* task, TaskBase::State state)
{
    mCriticalSection.lock();

    if (task->mState != state)
    {
        switch (state)
        {
        case TaskBase::cPrepare:
            if (task->mState == TaskBase::cCreated)
            {
                task->mState = TaskBase::cPrepare;
                appendToList_(mPrepareList, task);

                if (mPrepareThread == NULL || mPrepareThread->sendMessage(1, 1))
                {
                    mCriticalSection.unlock();
                    return true;
                }
            }

            break;

        case TaskBase::cPrepareDone:
            task->mState = TaskBase::cPrepareDone;
            task->mTaskListNode.erase();

            mCriticalSection.unlock();
            return true;

        case TaskBase::cRunning:
            task->mState = TaskBase::cRunning;
            task->mTaskListNode.erase();
            appendToList_(mActiveList, task);

            if (ResourceMgr::instance() != NULL)
                ResourceMgr::instance()->postCreate();

            task->enterCommon();

            mCriticalSection.unlock();
            return true;

        case TaskBase::cDying:
            task->mState = TaskBase::cDying;

            mCriticalSection.unlock();
            return true;

        case TaskBase::cDestroyable:
            if (task->mState == TaskBase::cRunning)
            {
                task->mState = TaskBase::cDestroyable;
                task->detachCalcImpl();
                task->detachDrawImpl();
                appendToList_(mDestroyableList, task);

                mCriticalSection.unlock();
                return true;
            }

            break;

        case TaskBase::cDead:
            task->exit();
            task->mState = TaskBase::cDead;
            task->mTaskListNode.erase();

            mCriticalSection.unlock();
            return true;
        }
    }

    mCriticalSection.unlock();
    return false;
}

void TaskMgr::destroyTaskSync(TaskBase* task)
{
    if (mParentFramework->mMethodTreeMgr->mCS.tryLock())
    {
        doDestroyTask_(task);
        mParentFramework->mMethodTreeMgr->mCS.unlock();
    }
}

void TaskMgr::doDestroyTask_(TaskBase* task)
{
    mCriticalSection.lock();

    TreeNode* node = task->mChild;
    while (node != NULL)
    {
        doDestroyTask_(static_cast<TTreeNode<TaskBase*>*>(node)->mData);
        node = task->mChild;
    }

    if (changeTaskState_(task, TaskBase::cDead))
    {
        task->detachAll();

        HeapArray heapArray(task->mHeapArray);
        for (s32 i = 0; i < HeapMgr::sRootHeaps.mPtrNum; i++)
        {
            Heap* heap = heapArray.mHeaps[i];
            if (heap != NULL)
                heap->destroy();
        }
    }

    mCriticalSection.unlock();
}

void TaskMgr::finalize()
{
    if (mPrepareThread != NULL)
    {
        mPrepareThread->quitAndDestroySingleThread(false);
        delete mPrepareThread;
        mPrepareThread = NULL;
    }

    if (mRootTask != NULL)
    {
        destroyTaskSync(mRootTask);
        mRootTask = NULL;
    }

    for (s32 i = 0; i < HeapMgr::sRootHeaps.mPtrNum; i++)
    {
        Heap* heap = mHeapArray.mHeaps[i];
        if (heap)
        {
            heap->destroy();
            mHeapArray.mHeaps[i] = NULL;
        }
    }
}

}  // namespace sead

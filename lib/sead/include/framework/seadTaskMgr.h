#ifndef SEAD_TASKMGR_H_
#define SEAD_TASKMGR_H_

#include <framework/seadHeapPolicies.h>
#include <framework/seadMethodTree.h>
#include <framework/seadTaskBase.h>
#include <heap/seadHeapMgr.h>
#include <thread/seadCriticalSection.h>

namespace sead
{
class DelegateThread;
class Framework;
class Heap;
class NullFaderTask;

class TaskMgr
{
public:
    struct InitializeArg
    {
    public:
        InitializeArg(const TaskBase::CreateArg& roottask_arg)
            : create_queue_size(0x20), prepare_stack_size(0x8000), prepare_priority(-1),
              roottask_create_arg(roottask_arg), heap(NULL), parent_framework(NULL)
        {
        }

        u32 create_queue_size;
        u32 prepare_stack_size;
        s32 prepare_priority;
        const TaskBase::CreateArg& roottask_create_arg;
        Heap* heap;
        Framework* parent_framework;
    };

    class TaskCreateContextMgr;

public:
    TaskMgr(const InitializeArg& arg);

    void appendToList_(TaskBase::List& ls, TaskBase* task);
    bool changeTaskState_(TaskBase* task, TaskBase::State state);
    void destroyTaskSync(TaskBase* task);
    void doDestroyTask_(TaskBase* task);
    void finalize();

    CriticalSection mCriticalSection;
    Framework* mParentFramework;
    DelegateThread* mPrepareThread;
    NullFaderTask* mNullFaderTask;
    TaskBase::List mPrepareList;
    TaskBase::List mPrepareDoneList;
    TaskBase::List mActiveList;
    TaskBase::List mStaticList;
    TaskBase::List mDyingList;
    TaskBase::List mDestroyableList;
    HeapArray mHeapArray;
    TaskCreateContextMgr* mTaskCreateContextMgr;
    u32 mMaxCreateQueueSize;
    TaskBase* mRootTask;
    TaskBase::CreateArg mRootTaskCreateArg;
    TaskMgr::InitializeArg mInitializeArg;
    MethodTreeNode mCalcDestructionTreeNode;
    u32 useless1;
    u32 useless2;
};

}  // namespace sead

#define SEAD_TASK_SINGLETON(CLASS)                                                                 \
public:                                                                                            \
    class SingletonDisposer_                                                                       \
    {                                                                                              \
    public:                                                                                        \
        ~SingletonDisposer_()                                                                      \
        {                                                                                          \
            if (mActive)                                                                           \
                CLASS::sInstance = nullptr;                                                        \
        }                                                                                          \
                                                                                                   \
        bool mActive = false;                                                                      \
    };                                                                                             \
                                                                                                   \
    static CLASS* instance() { return sInstance; }                                                 \
    static void setInstance_(sead::TaskBase* task);                                                \
    static void deleteInstance();                                                                  \
                                                                                                   \
    CLASS(const CLASS&) = delete;                                                                  \
    CLASS& operator=(const CLASS&) = delete;                                                       \
    CLASS(CLASS&&) = delete;                                                                       \
    CLASS& operator=(CLASS&&) = delete;                                                            \
                                                                                                   \
protected:                                                                                         \
    static CLASS* sInstance;                                                                       \
                                                                                                   \
    friend class SingletonDisposer_;                                                               \
    SingletonDisposer_ mSingletonDisposer;

#define SEAD_TASK_SINGLETON_IMPL(CLASS)                                                            \
    void CLASS::setInstance_(sead::TaskBase* task)                                                 \
    {                                                                                              \
        if (!sInstance)                                                                            \
        {                                                                                          \
            sInstance = static_cast<CLASS*>(task);                                                 \
            sInstance->mSingletonDisposer.mActive = true;                                          \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
            SEAD_ASSERT_MSG(false, "Create Singleton Twice (%s) : addr %p", #CLASS, sInstance);    \
        }                                                                                          \
    }                                                                                              \
                                                                                                   \
    void CLASS::deleteInstance()                                                                   \
    {                                                                                              \
        if (sInstance)                                                                             \
        {                                                                                          \
            sInstance->mTaskMgr->destroyTaskSync(sInstance);                                       \
            sInstance = nullptr;                                                                   \
        }                                                                                          \
    }                                                                                              \
                                                                                                   \
    CLASS* CLASS::sInstance = nullptr;

#endif  // SEAD_TASKMGR_H_

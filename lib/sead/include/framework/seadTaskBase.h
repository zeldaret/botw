#ifndef SEAD_TASKBASE_H_
#define SEAD_TASKBASE_H_

#include <container/seadTList.h>
#include <container/seadTreeNode.h>
#include <framework/seadHeapPolicies.h>
#include <framework/seadTaskID.h>
#include <heap/seadDisposer.h>
#include <prim/seadBitFlag.h>
#include <prim/seadDelegateEventSlot.h>
#include <prim/seadNamable.h>
#include <prim/seadRuntimeTypeInfo.h>

namespace sead
{
class FaderTaskBase;
class MethodTreeNode;
class TaskEvent;
class TaskMgr;
class TaskParameter;

class TaskBase : public TTreeNode<TaskBase*>, public IDisposer, public INamable
{
    SEAD_RTTI_BASE(TaskBase)

public:
    typedef TListNode<TaskBase*> ListNode;
    typedef TList<TaskBase*> List;

public:
    enum State
    {
        cCreated = 0,
        cPrepare = 1,
        cPrepareDone = 2,
        cSleep = 3,
        cRunning = 4,
        cDying = 5,
        cDestroyable = 6,
        cDead = 7
    };

    enum Tag
    {
        cSystem = 0,
        cApp = 1
    };

    struct CreateArg
    {
        typedef void (*SingletonFunc)(TaskBase*);

        TaskClassID factory;
        HeapPolicies heap_policies;
        TaskBase* parent;
        TaskParameter* parameter;
        FaderTaskBase* fader;
        TaskBase* src_task;
        TaskBase** created_task;
        DelegateEvent<TaskBase*>::Slot* create_callback;
        TaskUserID user_id;
        Tag tag;
        SingletonFunc instance_cb;
    };

public:
    explicit TaskBase(const TaskConstructArg& arg);
    TaskBase(const TaskConstructArg& arg, const char* name);
    virtual ~TaskBase();

    virtual void pauseCalc(bool b) = 0;
    virtual void pauseDraw(bool b) = 0;
    virtual void pauseCalcRec(bool b) = 0;
    virtual void pauseDrawRec(bool b) = 0;
    virtual void pauseCalcChild(bool b);
    virtual void pauseDrawChild(bool b);

    virtual void prepare();
    virtual void enterCommon();
    virtual void enter();
    virtual void exit();
    virtual void onEvent(const TaskEvent&);
    virtual void attachCalcImpl() = 0;
    virtual void attachDrawImpl() = 0;
    virtual void detachCalcImpl() = 0;
    virtual void detachDrawImpl() = 0;
    virtual const RuntimeTypeInfo::Interface* getCorrespondingMethodTreeMgrTypeInfo() const = 0;
    virtual MethodTreeNode* getMethodTreeNode(s32 method_type) = 0;
    virtual void onDestroy();

    TaskParameter* mParameter;
    BitFlag32 mInternalFlag;
    ListNode mTaskListNode;
    HeapArray mHeapArray;
    TaskMgr* mTaskMgr;
    State mState;
    Tag mTag;
    TaskClassID mClassID;
};

}  // namespace sead

#endif  // SEAD_TASKBASE_H_

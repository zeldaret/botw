#pragma once

#include <container/seadBuffer.h>
#include <prim/seadDelegate.h>
#include "KingSystem/Utils/Thread/Task.h"
#include "KingSystem/Utils/Types.h"

namespace ksys {
class TaskMgr;
class TaskQueue;
}  // namespace ksys

namespace ksys::act {

class ActorParam;
class BaseProc;

class BaseProcDeleter {
public:
    struct InitArg {
        sead::Heap* heap;
        TaskQueue* task_queue;
        int task_queue_size;
    };

    BaseProcDeleter();
    virtual ~BaseProcDeleter();

    void init(const InitArg& arg);
    bool requestPreDelete(BaseProc* proc);
    void requestUnloadActorParam(ActorParam* param);
    void unblockTasks();

private:
    enum class TaskLane : u8 {
        UnloadActorParam = 3,
        PreDelete = 4,
    };

    bool doPreDelete(void* proc);
    bool doUnloadParam(void* actor_param);

    TaskMgr* mTaskMgr{};
    TaskQueue* mTaskQueue{};
    sead::Buffer<void*> mBuffer;
    TaskDelegateT<BaseProcDeleter> mPreDeleteDelegate{this, &BaseProcDeleter::doPreDelete};
    TaskDelegateT<BaseProcDeleter> mUnloadActorParamDelegate{this, &BaseProcDeleter::doUnloadParam};
};
KSYS_CHECK_SIZE_NX150(BaseProcDeleter, 0x68);

}  // namespace ksys::act

#pragma once

#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Container/LockFreeQueue.h"

namespace sead {
class Heap;
}

namespace ksys::phys {

class RagdollController;

class RagdollControllerMgr {
public:
    RagdollControllerMgr();
    virtual ~RagdollControllerMgr();

    void init(sead::Heap* heap);

    bool addController(RagdollController* controller);
    void removeController(RagdollController* controller);

    void calc();
    void calc1();

private:
    util::LockFreeQueue<RagdollController> mControllers;
    sead::CriticalSection mCS;
};

}  // namespace ksys::phys

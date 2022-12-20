#pragma once

#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Container/LockFreeQueue.h"

namespace sead {
class Heap;
}

namespace ksys::phys {

class RagdollInstance;

class RagdollInstanceMgr {
public:
    RagdollInstanceMgr();
    virtual ~RagdollInstanceMgr();

    void init(sead::Heap* heap);

    bool addInstance(RagdollInstance* instance);
    void removeInstance(RagdollInstance* instance);

    void calc();
    void calc1();

private:
    util::LockFreeQueue<RagdollInstance> mInstances;
    sead::CriticalSection mCS;
};

}  // namespace ksys::phys

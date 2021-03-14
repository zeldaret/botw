#pragma once

#include <heap/seadDisposer.h>

namespace ksys::act {

// TODO: incomplete
class ActorSystem {
    SEAD_SINGLETON_DISPOSER(ActorSystem)
    ActorSystem();

public:
    void onBaseProcMgrCalc();
};

}  // namespace ksys::act

#pragma once

#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>

namespace ksys::act {

class ActorConstDataAccess;

// TODO: incomplete
class ActorSystem {
    SEAD_SINGLETON_DISPOSER(ActorSystem)
    ActorSystem();

public:
    void onBaseProcMgrCalc();

    bool getPlayer(ActorConstDataAccess* accessor);

    bool getAutoPlacementActorPos(const sead::SafeString& name, sead::Vector3f* pos) const;

    sead::Heap* getEmergencyHeap() const { return mEmergencyHeap; }
    const sead::Vector3f& getPlayerPos() const { return mPlayerPos; }

private:
    u8 temp_0x20[0xd0 - 0x20];
    sead::Heap* mEmergencyHeap;
    sead::Vector3f mPlayerPos;
};

}  // namespace ksys::act

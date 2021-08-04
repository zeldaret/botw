#pragma once

#include <heap/seadDisposer.h>
#include <mc/seadJobQueue.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {

struct ActorPhysics;

class MCMgrJob : sead::Job {

public:
    void invoke() override;

private:
    void* actorChemicalStuff;
    ActorPhysics* actorPhysics;
    short flags;
    const char* name;
    void* field_38;
};

class MCMgr {
    SEAD_SINGLETON_DISPOSER(MCMgr)

public:
    MCMgr();

    void* _0; // TODO: Add gsys::ISystemTaskCallback, as it is a base class of this one
    sead::FixedSizeJQ queue0;
    sead::FixedSizeJQ queue1;
    sead::FixedSizeJQ queue2;
    sead::FixedSizeJQ queue3;
    sead::FixedSizeJQ postBgPlayerAfter;
    sead::FixedSizeJQ queue4;
    sead::FixedSizeJQ placementMgrJobQueue;
    sead::FixedSizeJQ queue5;
    sead::FixedSizeJQ queue6;
    sead::FixedSizeJQ queue7;
    sead::FixedSizeJQ queues8[8];
    sead::Job0<MCMgr> calcControllerAndUiJob;
    sead::Job0<MCMgr> messageDispatcherJob;
    u32 flags;
    int field_BDC;
    MCMgrJob initProcessJobs[64];
    int numJobs;
    int calcJobCounterMaybe;
    void* gap_1BE8;
    sead::Delegate1R<MCMgr, void*, bool> invoker2;
    sead::Delegate1R<MCMgr, void*, bool> invoker3;
    sead::Delegate1R<MCMgr, void*, bool> invoker4;
};
KSYS_CHECK_SIZE_NX150(MCMgr, 0x1C50);

}  // namespace ksys

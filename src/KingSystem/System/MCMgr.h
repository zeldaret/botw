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
    void* mActorChemicalStuff;
    ActorPhysics* mActorPhysics;
    short mFlags;
    const char* mName;
    void* _38;
};

class MCMgr {
    SEAD_SINGLETON_DISPOSER(MCMgr)

public:
    MCMgr();

    void* _0; // TODO: Add gsys::ISystemTaskCallback, as it is a base class of this one
    sead::FixedSizeJQ mQueue0;
    sead::FixedSizeJQ mQueue1;
    sead::FixedSizeJQ mQueue2;
    sead::FixedSizeJQ mQueue3;
    sead::FixedSizeJQ mPostBgPlayerAfter;
    sead::FixedSizeJQ mQueue4;
    sead::FixedSizeJQ mPlacementMgrJobQueue;
    sead::FixedSizeJQ mQueue5;
    sead::FixedSizeJQ mQueue6;
    sead::FixedSizeJQ mQueue7;
    sead::FixedSizeJQ mQueues8[8];
    sead::Job0<MCMgr> mCalcControllerAndUiJob;
    sead::Job0<MCMgr> mMessageDispatcherJob;
    u32 mFlags;
    int _bdc;
    MCMgrJob mInitProcessJobs[64];
    int mNumJobs;
    int mCalcJobCounterMaybe;
    void* _1be8;
    sead::Delegate1R<MCMgr, void*, bool> mInvoker2;
    sead::Delegate1R<MCMgr, void*, bool> mInvoker3;
    sead::Delegate1R<MCMgr, void*, bool> mInvoker4;
};
KSYS_CHECK_SIZE_NX150(MCMgr, 0x1C50);

}  // namespace ksys

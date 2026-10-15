#pragma once

#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include <prim/seadDelegate.h>
#include <prim/seadSafeString.h>

#include "Game/AutoPlacement/AutoPlacementOwnerFields.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
}  // namespace ksys::act

namespace uking {

class AutoPlacementMgr {
    SEAD_SINGLETON_DISPOSER(AutoPlacementMgr)
public:
    AutoPlacementMgr();
    virtual ~AutoPlacementMgr();

    bool sub_7100659E40(ksys::act::Actor* actor, const sead::SafeString& actor_name, int count,
                        bool is_box);
    void sub_7100659F94(ksys::act::Actor* actor);

    // 0x0000007100654e44
    void threadFn(sead::Thread* thread, sead::MessageQueue::Element message);
    bool init(sead::Heap* heap);
    s32 sub_7100659158(s32 resource_idx, bool near_flow);
    void actorCreateCallback(ksys::act::Actor* actor);
    bool invoked3(s32 event);
    f32 invoked4(const AutoPlacementPoint* point);
    void preCalc();
    // 0x0000007100656030
    bool auto9();
    // 0x0000007100656d24
    bool auto2(const sead::SafeString& name, const sead::Vector3f& pos);
    // 0x0000007100659188
    bool auto0(const sead::Vector3f& pos, u32 placement_type);
    // 0x0000007100659350
    bool auto11(const sead::Vector3f& pos);

    // Original function at 0x71006592e8. Its service meaning is unknown.
    float sub_71006592E8(const sead::Vector3f& pos);

    // Inferred interface to the original water-depth query service.
    f32 sub_7100659230(const sead::Vector3f& pos);

    sead::DelegateThread* mThread = nullptr;
    sead::Delegate2<AutoPlacementMgr, sead::Thread*, sead::MessageQueue::Element> mDelegate{
        this, &AutoPlacementMgr::threadFn};
    sead::Atomic<u32> mWorkerState{sead::AtomicDirectInitTag{}, 0};
    u32 mFlags = 0;
    sead::SafeArray<AutoPlacementRequest, 300> mRequests;
    sead::SafeArray<AutoPlacement, 10> mPlacements{};
    sead::Buffer<u16> mSpawnLocationFlags;
    sead::SafeArray<ksys::act::BaseProcHandle, 8> mCreateHandles;
    sead::CriticalSection mCreateCS;
    sead::SafeArray<DeferredActorSpawn, 32> mDeferredSpawns{};
    sead::Vector3f mPlayerPosition = sead::Vector3f::zero;
    sead::Vector3f mPreviousPlayerPosition = sead::Vector3f::zero;
    AutoPlacement* mPendingPlacement = nullptr;
    AutoPlacementRequest* mPendingRequest = nullptr;
    s16 mPendingGroupIndex = 0;
    s8 mGridX = -1;
    s8 mGridZ = -1;
    u8 mCalcCooldown = 1;
    bool mReloadRequested = false;
    bool mPlacementUpdatePending = false;
    bool mDeferredUpdatePending = false;
    sead::Atomic<s32> mStopCount{sead::AtomicDirectInitTag{}, 0};
    sead::SafeArray<s32, 7> mActorCounts{};
    sead::SafeArray<s8, 7> mActorCooldowns{};
    sead::SafeArray<sead::PtrArray<ksys::map::Object>, 8> mObjectLists;
    AutoPlacementInfo mInfo;
    RoadNpcPlacementMgr mRoadNpcs;
    sead::Delegate1<AutoPlacementMgr, ksys::act::Actor*> mActorCreateDelegate{
        this, &AutoPlacementMgr::actorCreateCallback};
    StatisticsEntry* mWaterDepth = nullptr;
    StatisticsEntry* mForestDensity = nullptr;
    StatisticsEntry* mRouteDistance = nullptr;
    StatisticsEntry* mPlacementForbidden = nullptr;
    StatisticsEntry* mWaterDistance = nullptr;
    sead::Delegate1R<AutoPlacementMgr, s32, bool> mEventDelegate{this, &AutoPlacementMgr::invoked3};
    sead::Delegate1R<AutoPlacementMgr, const AutoPlacementPoint*, f32> mEligibilityDelegate{
        this, &AutoPlacementMgr::invoked4};
    sead::Delegate<AutoPlacementMgr> mPreCalcDelegate{this, &AutoPlacementMgr::preCalc};
};
KSYS_CHECK_SIZE_NX150(AutoPlacementMgr, 0x189e38);
static_assert(offsetof(AutoPlacementMgr, mRequests) == 0x58);
static_assert(offsetof(AutoPlacementMgr, mPlacements) == 0x41f8);
static_assert(offsetof(AutoPlacementMgr, mDeferredSpawns) == 0x5b118);
static_assert(offsetof(AutoPlacementMgr, mObjectLists) == 0x171e70);
static_assert(offsetof(AutoPlacementMgr, mInfo) == 0x171ef0);
static_assert(offsetof(AutoPlacementMgr, mRoadNpcs) == 0x172480);
static_assert(offsetof(AutoPlacementMgr, mActorCreateDelegate) == 0x189d90);

}  // namespace uking

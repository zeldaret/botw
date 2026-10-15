#pragma once

#include <container/seadBuffer.h>
#include <container/seadSafeArray.h>
#include <math/seadVector.h>
#include <prim/seadDelegate.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Map/mapRail.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
}
namespace ksys::res {
class Handle;
}

namespace uking {

struct AutoPlacementPoint {
    sead::Vector2f position;
    sead::Vector2f scale;
    f32 rotationY;
    u16 shape;
    u16 filterMask;
};
KSYS_CHECK_SIZE_NX150(AutoPlacementPoint, 0x18);

struct AutoPlacementPointResult {
    sead::Vector3f position;
    sead::Vector3f rotation;
    sead::Vector3f scale;
    u16 shape;
    u16 filterMask = 0;
};
KSYS_CHECK_SIZE_NX150(AutoPlacementPointResult, 0x28);

struct AutoPlacementPointResults {
    sead::SafeArray<AutoPlacementPointResult, 32> points;
    s32 count;
};
KSYS_CHECK_SIZE_NX150(AutoPlacementPointResults, 0x504);

class AutoPlacementPointHeightQuery;

class AutoPlacementInfo {
public:
    AutoPlacementInfo(const char* name, s32 num_filters, const char* const* filters);
    virtual ~AutoPlacementInfo();
    virtual bool parse(const al::ByamlIter& iter, sead::Heap* heap);
    bool init(sead::Heap* heap, bool keep_height);
    bool findPoints(const sead::Vector3f& position, bool apply_filter, s32 filter_mask,
                    AutoPlacementPointResults* results, f32 scale_multiplier);
    s32 gatherPoints(s32 x, s32 z, const sead::Vector3f& position, bool apply_filter,
                     s32 filter_mask, AutoPlacementPointResults* results,
                     AutoPlacementPointHeightQuery* height_query, f32 scale_multiplier);

    sead::FixedSafeString<32> mPath;
    sead::SafeString mName;
    ksys::res::Handle* mResource;
    sead::Buffer<AutoPlacementPoint> mPoints;
    sead::SafeArray<sead::Buffer<AutoPlacementPoint>, 80> mPointBins;
    sead::Buffer<const char*> mFilters;
    sead::Buffer<f32> mHeights;
    bool mKeepHeight;
};
KSYS_CHECK_SIZE_NX150(AutoPlacementInfo, 0x590);

class RailNavigation {
public:
    RailNavigation();
    virtual ~RailNavigation();
    virtual void reset();
    virtual void updatePath();
    virtual void advance(void* context, s32* junction_index, f32 distance);
    bool hasNextRail() const;

    sead::Vector3f mPosition;
    sead::Vector3f mTargetPosition;
    s32 mPointIndex;
    ksys::map::Rail* mRail;
    sead::Vector3f mPreviousPosition;
    sead::Vector3f mNextPosition;
    s32 mNextPointIndex;
    ksys::map::Rail* mNextRail;
    bool mForward;
    sead::SafeString mName;
    s8 mDirection;
    s8 mNumNames;
    bool mUseJunctions;
    sead::SafeArray<sead::FixedSafeString<32>, 32> mRailNames;
    sead::SafeArray<s8, 31> mPreviousJunctions;
    sead::SafeArray<s8, 31> mNextJunctions;
};
KSYS_CHECK_SIZE_NX150(RailNavigation, 0x7b8);

struct RoadNpcPlacementEntry {
    void onActorUpdate(ksys::act::Actor* actor, bool deleted);
    void onActorCreated(ksys::act::BaseProc* proc);
    bool update(bool pending);
    bool canSpawn(bool pending);

    ksys::act::BaseProcLink proc;
    sead::SafeString name;
    sead::Vector3f position;
    RailNavigation navigation;
    u16 flags;
    u8 category;
    f32 traverseDistanceSq;
    u32 createFlagId;
    u32 deleteFlagId;
    AutoPlacementInfo* info;
    sead::Delegate2<RoadNpcPlacementEntry, ksys::act::Actor*, bool> updateDelegate{
        this, &RoadNpcPlacementEntry::onActorUpdate};
    sead::Delegate1<RoadNpcPlacementEntry, ksys::act::BaseProc*> createDelegate{
        this, &RoadNpcPlacementEntry::onActorCreated};
};
KSYS_CHECK_SIZE_NX150(RoadNpcPlacementEntry, 0x840);

struct RoadNpcSpawnState {
    ksys::act::BaseProcHandle handle;
    RoadNpcPlacementEntry* pendingEntry;
};
KSYS_CHECK_SIZE_NX150(RoadNpcSpawnState, 0x18);

class RoadNpcPlacementMgr {
public:
    RoadNpcPlacementMgr();
    ~RoadNpcPlacementMgr();
    bool init(sead::Heap* heap);
    bool hasPendingSpawn() const;
    void finishSpawn();
    void update();
    void selectSpawn();
    bool createFromPoint(RoadNpcSpawnState* state, bool rest_station,
                         const sead::Vector3f* rotation, bool use_special_create_flag);
    bool queryActorPosition(const sead::SafeString& name, sead::Vector3f* position);

    sead::SafeArray<RoadNpcPlacementEntry, 45> mEntries;
    RoadNpcSpawnState mSpawnState;
    bool mEnabled;
    bool mUpdatePending;
    u32 mCreateWait;
    AutoPlacementInfo mInfo;
    sead::Delegate2R<RoadNpcPlacementMgr, const sead::SafeString&, sead::Vector3f*, bool>
        mPositionDelegate{this, &RoadNpcPlacementMgr::queryActorPosition};
};
KSYS_CHECK_SIZE_NX150(RoadNpcPlacementMgr, 0x17910);

}  // namespace uking

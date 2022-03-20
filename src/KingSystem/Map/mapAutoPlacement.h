#pragma once

#include <math/seadVector.h>
#include <prim/seadDelegate.h>
#include <prim/seadSafeString.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Physics/physMaterialMask.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {
class RayCastForRequest;
class RigidBody;
}  // namespace ksys::phys

namespace ksys::map {

class AutoPlacement;
struct AutoPlacementFlowRes;
class PlacementThing;

struct PlacementGroup {
    sead::SafeString a;
    u32 _10;
    u32 _14;
    u8 _18;
    u8 _19;
    u8 _1a;
    u8 _1b;
    u8 _1c;
    u8 _1d;
    u8 _1e;
    u8 _1f{};
    s16 _20;
    u16 _22{};
    u8 _24;
    u8 _25{};
    void* _28;
    void* _30;
    void* _38;
    void* _40;
    void* _48;
    void* _50;
    void* _58;
    void* _60;
    void* _68;
    sead::SafeString b;
    u32 _80{};
};
KSYS_CHECK_SIZE_NX150(PlacementGroup, 0x88);

class PlacementThing {
public:
    enum class State : u32 {
        Invalid,
        Uninitialized,
        Initialized,
        LayersDone,
        RaycastDone,
        PlacementDone,
    };

    explicit PlacementThing(bool set)
        : mDelegate{this, &PlacementThing::sub_7100650C28}, _8944(set) {}

    bool invoke();
    void stepRaycast();
    void sub_7100650C28(phys::RigidBody*);
    const char* getCurrentGroundMat() const;
    const char* getCurrentWaterSubMat() const;

private:
    friend class AutoPlacement;

    phys::RayCastForRequest* mRaycast{};
    u8 _8880{};
    u8 mUnderwater{};
    sead::Vector3f mVec1{};
    sead::Vector3f mQueryVec{};
    u32 _889c{};
    f32 _88a0 = 1.0f;
    phys::MaterialMask mMask1;
    phys::MaterialMask mMask2;
    f32 mWaterQuery = -1.0f;
    sead::Delegate1<PlacementThing, phys::RigidBody*> mDelegate;
    sead::CriticalSection mCS{};
    State mState;
    u8 _8944{};
    u8 _8945{};
};

struct ActorSpawnInfo {
    enum class SpawnLocation : u16 {
        CheckBirdSafetyArea = 1,

        // exclusive
        TrunkOrGlowStoneLocator = 2,
        _4 = 4,
        TrunkLocatorRandom = 8,
        _10 = 0x10,
        BranchLocatorRandom = 0x20,
        OnTreeLocator = 0x40,
        OnTreeLocatorRandom = 0x80,

        IsSnowBall = 0x100,
    };

    void calcSpawnLocations();

    sead::SafeString name{};
    AutoPlacementFlowRes* flow;
    u8 _18;
    u8 _19;
    sead::TypedBitFlag<SpawnLocation> spawn_location{};
    u16 _1c;
    u16 _1e;
};

class AutoPlacement {
public:
    AutoPlacement();
    ~AutoPlacement();

    bool sub_710064CBFC(sead::Heap* heap, u8 flag, s32 num_spawn, s32 num_obj);
    u32 sub_710064CD80(u32, u32);
    void sub_710064CF60(bool force);

    bool sub_710064ED60(const sead::SafeString& name, const sead::Vector3f& distance);

    void setSpawnInfo(const sead::SafeString& name, s32 count);
    void sub_710064DA54();

    bool sub_710064E178(const sead::SafeString& name, u32 placement_type,
                        const sead::Vector3f& pos);
    bool sub_710064EF24(ActorSpawnInfo* info, const sead::Vector3f& pos);
    void sub_710064F744(u8 a1, u8 a2);
    void incrementGroup();
    bool sub_7100650144(PlacementGroup* grp, bool check_exposure);
    s32 placeGroup(AutoPlacementFlowRes* res);
    s32 sub_7100650908();
    void stepAllRaycasts();
    void sub_7100650C28(phys::RigidBody* rb);

private:
    struct ObjectRef {
        Object* obj;
        void* _8;
    };

    s16 _0 = 0;
    s16 mGroupIdx = -1;
    u8 _4 = 0xFF;
    u8 _5 = 0xFF;
    s16 _6 = 0;
    u8 _8 = 0;
    u8 _9 = 2;
    sead::BitFlag<u8> mNearFlag{};
    sead::BitFlag<u8> _b{};
    u8 _c = 0;
    u8 _d = 0;
    u8 _e = 0;
    u8 _f = 0;
    u8 _10 = 0;
    s32 _14 = 0;
    sead::Buffer<ActorSpawnInfo> mSpawnInfo;
    sead::CriticalSection mCS{};
    sead::SafeArray<PlacementGroup, 0x100> mGroups{};
    sead::SafeString _8868{};
    PlacementThing mThing1{false};
    PlacementThing mThing2{false};
    PlacementThing mThing3{true};
    void* mX;
    sead::Buffer<ObjectRef> mObjectRefs;
};

}  // namespace ksys::map

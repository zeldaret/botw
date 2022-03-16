#include "KingSystem/Map/mapAutoPlacement.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/ActorSystem/actPhysicsUserTag.h"
#include "KingSystem/Ecosystem/ecoSystem.h"
#include "KingSystem/Map/mapAutoPlacementFlowMgr.h"
#include "KingSystem/Map/mapAutoPlacementMgr.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/World/worldWeatherMgr.h"

namespace ksys::map {

AutoPlacement::AutoPlacement() = default;

bool AutoPlacement::sub_710064CBFC(sead::Heap* heap, u8 flag, u32 idx, u32 num_obj) {
    mNearFlag = flag;

    if (!mSpawnInfo.tryAllocBuffer(idx, heap))
        return false;

    if (!mObjectRefs.tryAllocBuffer(num_obj, heap))
        return false;
    return true;
}

u32 AutoPlacement::sub_710064CD80(u32 a, u32 b) {
    auto calc = [](u32 x, u32 y, u32 a, u32 b) { return (1 - a + x < 3) & (1 - b + y < 3); };
    return calc(_4, _5, a, b);
}

void ActorSpawnInfo::calcSpawnLocations() {
    auto* mgr = ksys::act::InfoData::instance();
    al::ByamlIter iter;

    using namespace ksys::act::tags;

    spawn_location.makeAllZero();
    if (mgr == nullptr || !mgr->getActorIter(&iter, name.cstr()))
        return;

    if (mgr->hasTag(iter, CheckBirdSafetyArea))
        spawn_location.set(SpawnLocation::CheckBirdSafetyArea);
    if (mgr->hasTag(iter, IsSnowBall))
        spawn_location.set(SpawnLocation::IsSnowBall);

    if (mgr->hasTag(iter, CreateFromTrunkOrGlowStoneLocator))
        spawn_location.set(SpawnLocation::TrunkOrGlowStoneLocator);
    else if (mgr->hasTag(iter, 0x923A4962))
        spawn_location.set(SpawnLocation::_4);
    else if (mgr->hasTag(iter, CreateFromTrunkLocatorRandom))
        spawn_location.set(SpawnLocation::TrunkLocatorRandom);
    else if (mgr->hasTag(iter, 0x7881F260))
        spawn_location.set(SpawnLocation::_10);
    else if (mgr->hasTag(iter, CreateFromBranchLocatorRandom))
        spawn_location.set(SpawnLocation::BranchLocatorRandom);
    else if (mgr->hasTag(iter, CreateFromOnTreeLocator))
        spawn_location.set(SpawnLocation::OnTreeLocator);
    else if (mgr->hasTag(iter, CreateFromOnTreeLocatorRandom))
        spawn_location.set(SpawnLocation::OnTreeLocatorRandom);
}

void AutoPlacement::setSpawnInfo(const sead::SafeString& name, s32 count) {
    sub_710064CF60(false);
    ActorSpawnInfo* info = &mSpawnInfo[0];
    auto* res = AutoPlacementFlowMgr::instance()->getFlow(name, mNearFlag == 0xff);
    if (res != nullptr) {
        info->name = name;
        info->_10 = res;
        info->_19 = 0;
        s32 value = std::min(count, 255);
        info->_18 = value;
        info->_1c = value * 30;
        info->_1e = 0;
        info->calcSpawnLocations();
        _d = true;
        _8 = 0;
    } else {
        _d = false;
    }
}

void AutoPlacement::sub_710064DA54() {
    sub_710064CF60(false);
    _8 = 2;
}

static sead::Buffer<ksys::eco::AreaItemType> sPlacementTypesBuffer((ksys::eco::AreaItemType[]){
    ksys::eco::AreaItemType::Enemy,
    ksys::eco::AreaItemType::Animal,
    ksys::eco::AreaItemType::Insect,
    ksys::eco::AreaItemType::Fish,
    ksys::eco::AreaItemType::Bird,
    ksys::eco::AreaItemType::AutoPlacementMaterial,
});

// NON_MATCHING: stack
bool AutoPlacement::sub_710064E178(const sead::SafeString& name, u32 placement_type,
                                   const sead::Vector3f& pos) {
    if (mNearFlag == 0xFE)
        return true;

    auto* eco = ksys::eco::Ecosystem::instance();
    if (eco == nullptr)
        return false;

    s32 area = eco->getFieldMapArea(pos.x, pos.z);
    if (area < 0)
        return false;

    ksys::eco::AreaItemSet item_set;
    eco->getAreaItems(area, sPlacementTypesBuffer[placement_type], &item_set);

    for (int i = 0; i < item_set.count; ++i) {
        const auto& item = item_set.items[i];
        if (item.num > 0.0f && name == item.name)
            return true;
    }
    return false;
}

// NON_MATCHING: blocked by raycast
bool PlacementThing::invoke() {
    auto lock = sead::makeScopedLock(mCS);

    if (AutoPlacementMgr::instance()->auto9())
        return true;

    if (mRaycast == nullptr || mState != State::kNotInvoked)
        return false;

    mRaycast->addContactLayer(phys::ContactLayer::EntityGround);
    mRaycast->addContactLayer(phys::ContactLayer::EntityGroundRough);
    mRaycast->addContactLayer(phys::ContactLayer::EntityGroundSmooth);
    mRaycast->addContactLayer(phys::ContactLayer::EntityAirWall);
    mRaycast->addContactLayer(phys::ContactLayer::EntityGroundObject);
    mRaycast->addContactLayer(phys::ContactLayer::EntityTree);

    if (_8944) {
        sead::Vector3f v1 = mVec1 + sead::Vector3f{0, 4, 30};
        sead::Vector3f v2 = mVec1 - sead::Vector3f{0, 4, 30};
        mRaycast->sub_7100FC38A0(v1, v2);
    } else {
        sead::Vector3f v1{mVec1.x, 2000.0f, mVec1.z};
        sead::Vector3f v2{mVec1.x, -100.0f, mVec1.z};
        mRaycast->sub_7100FC38A0(v1, v2);
        // void** p = &mRaycast->mGroups[0]._68;
        // *p = &mDelegate;
    }

    mState = State::kInvoked;
    return true;
}

bool AutoPlacement::sub_7100650144(PlacementGroup* grp, bool check_exposure) {
    if (grp->_1d == 0xFF)
        return false;
    if (grp->_20 == -1)
        return false;

    auto* object = mObjectRefs[grp->_20].obj;
    if (object == nullptr)
        return false;

    if (object->shouldSkipSpawn()) {
        return true;
    }

    if (object->getProc() == nullptr && object->getFlags0().isOn(Object::Flag0::_80))
        return true;

    if (grp->_1d != 2)
        return false;

    if (check_exposure && !ksys::world::WeatherMgr::isExposureZero())
        return true;
    return false;
}

bool AutoPlacement::sub_710064EF24(ActorSpawnInfo* info, const sead::Vector3f& pos) {
    auto* mgr = AutoPlacementMgr::instance();
    u32 placement_type = info->_10->placement_type;
    if (mgr->auto0(pos, placement_type)) {
        if (mNearFlag != 0xFF) {
            return false;
        }
        if (info->name.findIndex("Enemy_Dragon") == -1) {
            return false;
        }
    }

    if ((mNearFlag != 0xFF && mgr->auto11(pos)) ||
        (!sub_710064E178(info->name, placement_type, pos))) {
        return false;
    }

    if (mNearFlag != 0xFE && mNearFlag != 0xFF) {
        if (AutoPlacementMgr::instance()->auto2(info->name, pos))
            return false;
    }
    return true;
}

void AutoPlacement::sub_710064F744(u8 a1, u8 a2) {
    if (mNearFlag != 0xFF)
        return;
    if (mGroupIdx < 0)
        return;

    auto& grp = mGroups[mGroupIdx];
    if (!grp._80) {
        grp._1a = a1;
        grp._1b = a2;
    }
}

void AutoPlacement::incrementGroup() {
    if (mGroupIdx < 0)
        return;
    mGroupIdx++;
}

s32 AutoPlacement::placeGroup(AutoPlacementFlowRes* res) {
    if (mGroupIdx < 0) {
        return -1;
    }

    mThing2.mRaycast = mThing1.mRaycast;
    _6 = 0;
    _b = 0xFF;

    auto& grp = mGroups[mGroupIdx];
    if (grp.b.isEmpty()) {
        return -1;
    }

    _8868 = sead::SafeString::cEmptyString;
    int tmp = 0;
    res->start(this, grp.a, &tmp);
    if (!_9)
        return -1;
    _9 = 0;

    return mGroupIdx;
}

s32 AutoPlacement::sub_7100650908() {
    if (mGroupIdx < 0) {
        return -1;
    }
    return mGroups[mGroupIdx]._1c;
}

void AutoPlacement::stepAllRaycasts() {
    mThing1.stepRaycast();
    mThing2.stepRaycast();
    mThing3.stepRaycast();
}

void PlacementThing::stepRaycast() {
    auto lock = sead::makeScopedLock(mCS);

    if (AutoPlacementMgr::instance()->auto9()) {
        if (mRaycast != nullptr) {
            mRaycast->release();
            mRaycast = nullptr;
        }
        mState = State::kInvalid;
        _8880 = _8944;
        return;
    }

    State next;

    switch (mState) {
    case State::kFree:
        mRaycast = Raycast::create(nullptr, 1);
        next = mRaycast != nullptr ? State::kNotInvoked : State::kInvalid;
        break;
    case State::kInvoked:
        mRaycast->sub_7100FC55AC(0);
        next = State::kDone;
        break;
    case State::kWaiting:
        if (mRaycast != nullptr) {
            mRaycast->release();
            next = State::kInvalid;
            mRaycast = nullptr;
        } else {
            next = State::kInvalid;
        }
        break;
    default:
        return;
    }
    mState = next;
}

void AutoPlacement::sub_7100650C28(phys::RigidBody* rb) {
    if (rb == nullptr)
        return;

    if (rb->getContactLayer() == phys::ContactLayer::EntityTree)
        mNearFlag.setDirect(1);

    auto* tag = sead::DynamicCast<act::PhysicsUserTag>(rb->getUserTag());
    if (tag == nullptr)
        return;

    auto* actor = tag->getActor();
    if (actor == nullptr)
        return;

    mNearFlag.set(ksys::act::hasTag(actor, act::tags::Tree) ||
                  ksys::act::hasTag(actor, act::tags::AutoPlacementForbidCreate));

    _b.set(actor->getName() == "AirWallHorse");
}

const char* PlacementThing::getCurrentGroundMat() const {
    if (mWaterQuery > 0.0f) {
        return mMask2.getMaterialName();
    } else {
        return mMask1.getMaterialName();
    }
}

const char* PlacementThing::getCurrentWaterSubMat() const {
    if (mWaterQuery > 0.0f) {
        return mMask2.getSubMaterialName();
    } else {
        return mMask1.getSubMaterialName();
    }
}

}  // namespace ksys::map

#include "Game/AutoPlacement/AutoPlacement.h"
#include <random/seadGlobalRandom.h>
#include <thread/seadThread.h>
#include <time/seadTickSpan.h>
#include "Game/AutoPlacement/AutoPlacementCreateGroupsInterfaces.h"
#include "Game/AutoPlacement/AutoPlacementFlowMgr.h"
#include "Game/AutoPlacement/AutoPlacementLocatorCache.h"
#include "Game/AutoPlacement/AutoPlacementMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/ActorSystem/actPhysicsUserTag.h"
#include "KingSystem/Ecosystem/ecoSystem.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physRayCastForRequest.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/World/worldWeatherMgr.h"

namespace uking {

AutoPlacement::AutoPlacement() = default;
AutoPlacement::~AutoPlacement() = default;

bool AutoPlacement::sub_710064CBFC(sead::Heap* heap, u8 flag, s32 num_spawn, s32 num_obj) {
    mNearFlag = flag;

    if (!mSpawnInfo.tryAllocBuffer(num_spawn, heap))
        return false;

    if (num_obj > 0 && !mObjectRefs.tryAllocBuffer(num_obj, heap))
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

// NON_MATCHING: the complete body has a different compiler layout.
void AutoPlacement::sub_710064CF60(bool force) {
    if (mNearFlag == 0xff && !force) {
        for (s32 i = 0; i < _0; ++i) {
            auto& group = mGroups[i];
            const u32 dx = u32(group._18) + 1 - _4;
            const u32 dz = u32(group._19) + 1 - _5;
            if (dx <= 2 && dz < 3)
                continue;

            const s32 last = _0 - 1;
            if (i == last) {
                group._1e = 0;
            } else {
                auto& tail = mGroups[last];
                group = tail;
                tail._1e = 0;
                --i;
            }
            --_0;
        }
    } else {
        {
            auto lock = sead::makeScopedLock(mCS);
            _0 = 0;
        }
        for (auto& group : mGroups)
            group._1e = 0;
    }

    // Preserve the original wrapping word increment.
    _14 = static_cast<s32>(static_cast<u32>(_14) + 1);
    _c = 0;
    mGroupIdx = -1;
    _9 = 0;
    PlacementThing* queries[] = {&mThing1, &mThing2, &mThing3};
    for (auto* query : queries) {
        auto lock = sead::makeScopedLock(query->mCS);
        if (query->mRaycast)
            query->mState = PlacementThing::State::PlacementDone;
    }

    for (s32 i = 0; i < mNumObjectRefs; ++i) {
        const s32 index = mObjectRefs[i].locatorCacheIndex;
        if (index >= 0) {
            const u32 bit = 1u << (u32(static_cast<s8>(static_cast<u8>(mNearFlag))) & 31);
            gActorLocators[index].usedModes.reset(bit);
        }
    }
    mNumObjectRefs = 0;
}

void AutoPlacement::setSpawnInfo(const sead::SafeString& name, s32 count) {
    sub_710064CF60(false);
    ActorSpawnInfo* info = &mSpawnInfo[0];
    auto* flow = AutoPlacementFlowMgr::instance()->getFlow(name, mNearFlag == 0xff);
    if (flow != nullptr) {
        info->name = name;
        info->flow = flow;
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

ksys::eco::AreaItemType sPlacementItemTypesData[] = {
    ksys::eco::AreaItemType::Enemy,  ksys::eco::AreaItemType::Animal,
    ksys::eco::AreaItemType::Insect, ksys::eco::AreaItemType::Fish,
    ksys::eco::AreaItemType::Bird,   ksys::eco::AreaItemType::AutoPlacementMaterial,
};
sead::Buffer<ksys::eco::AreaItemType> sPlacementItemTypes{sPlacementItemTypesData};

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
    eco->getAreaItems(area, sPlacementItemTypes[placement_type], &item_set);

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

    if (mRaycast == nullptr || mState != State::Initialized)
        return false;

    mRaycast->enableLayer(ksys::phys::ContactLayer::EntityGround);
    mRaycast->enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
    mRaycast->enableLayer(ksys::phys::ContactLayer::EntityGroundSmooth);
    mRaycast->enableLayer(ksys::phys::ContactLayer::EntityAirWall);
    mRaycast->enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    mRaycast->enableLayer(ksys::phys::ContactLayer::EntityTree);

    if (_8944) {
        sead::Vector3f v1 = mVec1 + sead::Vector3f{0, 4, 30};
        sead::Vector3f v2 = mVec1 - sead::Vector3f{0, 4, 30};
        mRaycast->setStartAndEnd(v1, v2);
    } else {
        sead::Vector3f v1{mVec1.x, 2000.0f, mVec1.z};
        sead::Vector3f v2{mVec1.x, -100.0f, mVec1.z};
        mRaycast->setStartAndEnd(v1, v2);
        mRaycast->setCallback(&mDelegate);
    }

    mState = State::LayersDone;
    return true;
}

// NON_MATCHING: compiler layout and register allocation differ.
bool PlacementThing::processRaycastResult() {
    auto lock = sead::makeScopedLock(mCS);

    if (AutoPlacementMgr::instance()->auto9()) {
        _8880 = _8944;
        return true;
    }

    if (mRaycast == nullptr || mState != State::RaycastDone) {
        _8880 = _8944;
        return true;
    }

    if (!mRaycast->hasCastResult())
        return false;

    const bool has_hit = mRaycast->hasHit();
    if (_8944) {
        if (has_hit) {
            _8880 = 1;
            mState = State::PlacementDone;
            return true;
        }
    } else if (has_hit && !mHasForbiddenHit) {
        if (mRaycast->isLayerEnabled(ksys::phys::ContactLayer::EntityWater)) {
            sead::Vector3f hit_position;
            mRaycast->getHitPosition(&hit_position);
            mMask2.set(mRaycast->getMaterialMaskData());
            mWaterQuery = hit_position.y - mQueryVec.y;
            mState = State::PlacementDone;
            return true;
        }

        if (mHasAirWallHorseHit && mRaycast->getGroundHit() == ksys::phys::GroundHit::Animal) {
            sead::Vector3f hit_position;
            mRaycast->getHitPosition(&hit_position);
            const sead::Vector3f end = mRaycast->getEnd();
            mRaycast->reset();
            mRaycast->setStartAndEnd(hit_position, end);
            mRaycast->setGroundHit(ksys::phys::GroundHit::HitAll);
            mState = State::PlacementDone;
            return true;
        }

        mRaycast->getHitPosition(&mQueryVec);
        _8880 = 1;
        mRaycast->getHitNormal(&mGroundNormal);
        mMask1.set(mRaycast->getMaterialMaskData());
        mRaycast->reset();
        mRaycast->enableLayer(ksys::phys::ContactLayer::EntityWater);
        const sead::Vector3f start{mQueryVec.x, 1000.0f, mQueryVec.z};
        mRaycast->setStartAndEnd(start, mQueryVec);
        mState = State::LayersDone;
        return false;
    }

    if (!_8944 && _8880) {
        mState = State::PlacementDone;
        return true;
    }

    if (!_8944)
        mQueryVec = mRaycast->getStart();
    const u8 next_index = _8945 + 1;
    _8945 = next_index;
    if (next_index == 8) {
        mState = State::PlacementDone;
        return true;
    }

    const s32 signed_index = static_cast<s8>(next_index);
    const u32 angle_index = (u32(next_index) << 29) - static_cast<u32>(signed_index);
    f32 offset_x;
    f32 offset_z;
    sead::Mathf::sinCosIdx(&offset_x, &offset_z, angle_index);
    offset_x *= 30.0f;
    offset_z *= 30.0f;

    mRaycast->reset();
    const sead::Vector3f offset{offset_x, 4.0f, offset_z};
    const sead::Vector3f start = mVec1 + offset;
    const sead::Vector3f end = mVec1 - offset;
    mRaycast->setStartAndEnd(start, end);
    mState = State::LayersDone;
    return false;
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

    if (object->getProc() == nullptr && object->getFlags0().isOn(ksys::map::Object::Flag0::_80))
        return true;

    if (grp->_1d != 2)
        return false;

    if (check_exposure && !ksys::world::WeatherMgr::isExposureZero())
        return true;
    return false;
}

bool AutoPlacement::sub_710064EF24(ActorSpawnInfo* info, const sead::Vector3f& pos) {
    auto* mgr = AutoPlacementMgr::instance();
    u32 placement_type = info->flow->placement_type;
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

// NON_MATCHING: the complete bodies have different compiler layouts.
void AutoPlacement::sub_710064E344(AutoPlacementFlowRes* flow, s32 group_count, f32 group_radius,
                                   f32 offset_pos_y, s32 equip_weapon_actor_count,
                                   const sead::SafeString& ride_list, bool mimicry) {
    if (_0 > 255)
        return;

    const s32 resource_idx = static_cast<s8>(flow->idx);
    sead::Matrix34f transform = sead::Matrix34f::ident;
    s32 object_ref_index = -1;
    if (flow->spawn_location_flags & 1) {
        auto& query = mThing3;
        const auto* active_query = mActiveQuery;
        query.mCS.lock();
        if (AutoPlacementMgr::instance()->auto9()) {
            query.mCS.unlock();
            return;
        }
        if (query.mState != PlacementThing::State::Invalid) {
            if (query.mState != PlacementThing::State::PlacementDone)
                query.mState = PlacementThing::State::PlacementDone;
            query.mCS.unlock();
            return;
        }
        query._8880 = 0;
        query.mWaterQuery = -1.0f;
        query.mUnderwater = 0;
        query.mHasForbiddenHit = 0;
        query.mHasAirWallHorseHit = 0;
        query.mState = PlacementThing::State::Uninitialized;
        query.mVec1 = active_query->mQueryVec;
        query._8945 = 0;
        query.mCS.unlock();

        auto state = query.mState;
        if (state != PlacementThing::State::Invalid &&
            state != PlacementThing::State::PlacementDone) {
            const auto delay = sead::TickSpan::makeFromMilliSeconds(1);
            do {
                if (state == PlacementThing::State::RaycastDone) {
                    if (query.processRaycastResult() && query._8880 && !query.mHasForbiddenHit)
                        return;
                } else if (state == PlacementThing::State::Initialized) {
                    query.invoke();
                }
                sead::Thread::sleep(delay);
                state = query.mState;
            } while (state != PlacementThing::State::Invalid &&
                     state != PlacementThing::State::PlacementDone);
        }
        if (query._8880 && !query.mHasForbiddenHit)
            return;
    }

    u8 placement_mode;
    if (flow->spawn_location_flags & 2) {
        placement_mode = sead::GlobalRandom::instance()->getF32() < 0.5f ? 0 : 2;
    } else if (flow->spawn_location_flags & 4) {
        placement_mode = 0;
    } else {
        const f32 branch_random = sead::GlobalRandom::instance()->getF32();
        if ((flow->spawn_location_flags & 8) && branch_random < 0.5f) {
            placement_mode = 0;
        } else if (flow->spawn_location_flags & 0x10) {
            placement_mode = 1;
        } else {
            const f32 trunk_random = sead::GlobalRandom::instance()->getF32();
            if ((flow->spawn_location_flags & 0x20) && trunk_random < 0.5f) {
                placement_mode = 1;
            } else if (flow->spawn_location_flags & 0x40) {
                placement_mode = 3;
            } else {
                const f32 tree_random = sead::GlobalRandom::instance()->getF32();
                placement_mode =
                    (flow->spawn_location_flags & 0x80) && tree_random < 0.5f ? 3 : 0xff;
            }
        }
    }
    const bool has_locator_transform = placement_mode != 0xff;
    if (has_locator_transform) {
        if (mNearFlag > 0xfd)
            return;
        if (!sub_710064DE34(flow->unit_name, &transform, &object_ref_index, placement_mode,
                            resource_idx))
            return;
    }

    mCS.lock();
    const u16 old_count = static_cast<u16>(_0);
    const s32 group_index = old_count > 255 ? 0 : _0;
    ++_0;
    auto& group = mGroups[group_index];
    group._1e = 1;
    group.a = flow->unit_name;
    group.pos = mActiveQuery->mQueryVec;
    s32 count = group_count;
    if (has_locator_transform) {
        group.transform = transform;
        if (count < 1)
            count = 1;
    } else {
        group.transform.makeIdentity();
        group.transform.setTranslation(group.pos);
    }
    group._1a = static_cast<u8>(count);
    if (mNearFlag == 0xfe)
        group._1a = static_cast<u8>(group_count < 1 ? 1 : group_count);
    group._22 = mWeatherMask;
    group._25 = mTimeDivisionMask;
    group._1c = static_cast<u8>(resource_idx);
    group.equipCategory = -1;
    if (mNearFlag != 0xff &&
        AutoPlacementMgr::instance()->sub_7100659158(resource_idx, false) == 0) {
        ksys::eco::AreaItemSet items;
        const auto* item = sub_7100657D2C(&items, group.pos, flow->unit_name);
        group.equipCategory =
            static_cast<s8>(sub_7100657EC4(item, static_cast<s8>(static_cast<u8>(_b))));
    }
    group._20 = object_ref_index;
    group.radius = group_radius;
    group.heightOffset = offset_pos_y;
    group.b = ride_list;
    group._1d = placement_mode;
    group._1f = 0;
    if (flow->unit_name.cstr()[0] == '\0') {
        group.traverseDistPlus100 = 0.0f;
        group.traverseDist = 0.0f;
    } else {
        group.traverseDistPlus100 = getActorTraverseDistPlus100(1.0f, flow->unit_name);
        group.traverseDist = getActorTraverseDist(1.0f, flow->unit_name);
    }
    if (mNearFlag == 0xff && sead::GlobalRandom::instance()->getF32() < 0.5f)
        group._1f |= 1;
    if (mimicry)
        group._1f |= 2;
    if (flow->spawn_location_flags & 0x100)
        group._1f |= 4;
    group._18 = _4;
    group._1b = static_cast<u8>(equip_weapon_actor_count);
    group._24 = 0;
    group._19 = _5;
    group._80 = 0;
    mCS.unlock();
}

bool AutoPlacement::sub_710064F54C(const sead::SafeString& unit_name, s32 min_count, s32 max_count,
                                   s32 resource_idx, bool mimicry) {
    s64 group_index = mGroupIdx;
    if (group_index < 0)
        return false;

    const auto& group = mGroups[s32(group_index)];
    if (group._1e == 0)
        return false;
    if (unit_name != group.a)
        return false;
    if (group._1c != resource_idx)
        return false;
    if ((mimicry ^ ((group._1f & 2) >> 1)) & 1)
        return false;

    if (u8(mNearFlag) > 0xfd)
        return true;

    const auto& query_pos = mActiveQuery->mQueryVec;
    const f32 dx = query_pos.x - group.pos.x;
    const f32 dz = query_pos.z - group.pos.z;
    const f32 radius = group.radius;
    if (!(dx * dx + dz * dz <= radius * radius))
        return false;

    if (min_count <= group._1a && group._1a <= max_count)
        return true;
    return group._1d != 0xff;
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

    mActiveQuery = &mThing2;
    mNearCreateWaitFrame = 0;
    _b = 0xFF;

    auto& grp = mGroups[mGroupIdx];
    if (grp.a.isEmpty()) {
        return -1;
    }

    _8868 = sead::SafeString::cEmptyString;
    u16 spawn_location_flags = 0;
    res->start(this, grp.a.cstr(), &spawn_location_flags);
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
        mState = State::Invalid;
        _8880 = _8944;
        return;
    }

    State next;

    switch (mState) {
    case State::Uninitialized:
        mRaycast =
            ksys::phys::RayCastForRequest::allocRequest(nullptr, ksys::phys::GroundHit::Animal);
        next = mRaycast != nullptr ? State::Initialized : State::Invalid;
        break;
    case State::LayersDone:
        mRaycast->submitRequest(ksys::phys::ContactLayerType::Entity);
        next = State::RaycastDone;
        break;
    case State::PlacementDone:
        if (mRaycast != nullptr) {
            mRaycast->release();
            next = State::Invalid;
            mRaycast = nullptr;
        } else {
            next = State::Invalid;
        }
        break;
    default:
        return;
    }
    mState = next;
}

void PlacementThing::sub_7100650C28(ksys::phys::RigidBody* rb) {
    if (rb == nullptr)
        return;

    if (rb->getContactLayer() == ksys::phys::ContactLayer::EntityTree)
        mHasForbiddenHit = 1;

    auto* tag = sead::DynamicCast<ksys::act::PhysicsUserTag>(rb->getUserTag());
    if (tag == nullptr)
        return;

    auto* actor = tag->getActor();
    if (actor == nullptr)
        return;

    mHasForbiddenHit |= ksys::act::hasTag(actor, ksys::act::tags::Tree) ||
                        ksys::act::hasTag(actor, ksys::act::tags::AutoPlacementForbidCreate);

    mHasAirWallHorseHit |= actor->getName() == "AirWallHorse";
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

bool AutoPlacement::getActorToSpawn(sead::SafeString* name, sead::Matrix34f* transform,
                                    sead::SafeString* ride_name, s32* rotation_mode,
                                    s32* equipment_count, bool* use_spawn_index, s32* count,
                                    bool* special_spawn, s32* equip_category) {
    if (mGroupIdx < 0)
        return false;

    const auto& group = mGroups[mGroupIdx];
    *name = group.a;
    *ride_name = group.b;
    *rotation_mode = s8(group._1d);
    *transform = group.transform;
    *special_spawn = (group._1f & 2) != 0;
    *equip_category = group.equipCategory;

    if (mNearFlag == 0xff) {
        *use_spawn_index = (group._1f & 1) != 0;
        *equipment_count = s8(group._1b);
        *count = s32(group._1a) - group._80;
    } else {
        *use_spawn_index = false;
        *equipment_count = -1;
        *count = 1;
    }

    const auto& current_group = mGroups[mGroupIdx];
    sead::Vector3f pos;
    if (current_group._1d != 0xff) {
        current_group.transform.getTranslation(pos);
    } else {
        pos = mThing2.mQueryVec;
        f32 height = pos.y;
        if (mThing2.mUnderwater)
            height += mThing2.mWaterQuery;
        height += current_group.heightOffset;
        pos.y = height < pos.y ? pos.y : height;
    }
    if (s8(group._1d) == -1)
        transform->setTranslation(pos);
    return true;
}

}  // namespace uking

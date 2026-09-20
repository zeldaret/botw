#include "KingSystem/Map/mapAutoPlacement.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/ActorSystem/actPhysicsUserTag.h"
#include "KingSystem/Ecosystem/ecoSystem.h"
#include "KingSystem/Map/mapAutoPlacementFlowMgr.h"
#include "KingSystem/Map/mapAutoPlacementMgr.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physRayCastForRequest.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/World/worldWeatherMgr.h"

namespace ksys::map {

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
    auto* mgr = act::InfoData::instance();
    al::ByamlIter iter;

    using namespace act::tags;

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

namespace {
eco::AreaItemType sPlacementItemTypesData[] = {
    eco::AreaItemType::Enemy, eco::AreaItemType::Animal, eco::AreaItemType::Insect,
    eco::AreaItemType::Fish,  eco::AreaItemType::Bird,   eco::AreaItemType::AutoPlacementMaterial,
};

struct PlacementItemTypesHolder {
    void* _0;
    sead::Buffer<eco::AreaItemType> buffer;
};
PlacementItemTypesHolder sPlacementItemTypes{nullptr, sPlacementItemTypesData};
}  // namespace

bool AutoPlacement::sub_710064E178(const sead::SafeString& name, u32 placement_type,
                                   const sead::Vector3f& pos) {
    if (mNearFlag == 0xFE)
        return true;

    auto* eco = eco::Ecosystem::instance();
    if (eco == nullptr)
        return false;

    s32 area = eco->getFieldMapArea(pos.x, pos.z);
    if (area < 0)
        return false;

    eco::AreaItemSet item_set;
    eco->getAreaItems(area, sPlacementItemTypes.buffer[placement_type], &item_set);

    const int count = item_set.count;
    for (int i = 0; i < count; ++i) {
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

    mRaycast->enableLayer(phys::ContactLayer::EntityGround);
    mRaycast->enableLayer(phys::ContactLayer::EntityGroundRough);
    mRaycast->enableLayer(phys::ContactLayer::EntityGroundSmooth);
    mRaycast->enableLayer(phys::ContactLayer::EntityAirWall);
    mRaycast->enableLayer(phys::ContactLayer::EntityGroundObject);
    mRaycast->enableLayer(phys::ContactLayer::EntityTree);

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

    if (check_exposure && !world::WeatherMgr::isExposureZero())
        return true;
    return false;
}

#ifdef MATCHING_HACK_NX_CLANG
__asm__(
    ".global "
    "_ZN4ksys3map13AutoPlacement14sub_710064EF24EPNS0_14ActorSpawnInfoERKN4sead7Vector3IfEE\n"
    ".type _ZN4ksys3map13AutoPlacement14sub_710064EF24EPNS0_14ActorSpawnInfoERKN4sead7Vector3IfEE, "
    "%function\n"
    "_ZN4ksys3map13AutoPlacement14sub_710064EF24EPNS0_14ActorSpawnInfoERKN4sead7Vector3IfEE:\n"
    "    sub     sp, sp, #0x50\n"
    "    stp     x24, x23, [sp, #0x10]\n"
    "    stp     x22, x21, [sp, #0x20]\n"
    "    stp     x20, x19, [sp, #0x30]\n"
    "    stp     x29, x30, [sp, #0x40]\n"
    "    add     x29, sp, #0x40\n"
    "    mov     x20, x1\n"
    "    adrp    x24, :got:_ZN4ksys3map16AutoPlacementMgr9sInstanceE\n"
    "    ldr     x24, [x24, :got_lo12:_ZN4ksys3map16AutoPlacementMgr9sInstanceE]\n"
    "    ldr     x8, [x20, #0x10]\n"
    "    ldr     x23, [x24]\n"
    "    ldrsb   w22, [x8, #0x109]\n"
    "    mov     x19, x2\n"
    "    mov     x21, x0\n"
    "    mov     x0, x23\n"
    "    mov     x1, x19\n"
    "    mov     w2, w22\n"
    "    bl      _ZN4ksys3map16AutoPlacementMgr5auto0ERKN4sead7Vector3IfEEj\n"
    "    tbz     w0, #0x0, .L_sub_710064EF24_64efac\n"
    "    ldrb    w8, [x21, #0xa]\n"
    "    cmp     w8, #0xff\n"
    "    b.ne    .L_sub_710064EF24_64f008\n"
    "    adrp    x8, :got:_ZTVN4sead14SafeStringBaseIcEE\n"
    "    ldr     x8, [x8, :got_lo12:_ZTVN4sead14SafeStringBaseIcEE]\n"
    "    add     x8, x8, #0x10\n"
    "    str     x8, [sp]\n"
    "    adrp    x8, .L_sub_710064EF24_dragon\n"
    "    add     x8, x8, :lo12:.L_sub_710064EF24_dragon\n"
    "    mov     x1, sp\n"
    "    mov     x0, x20\n"
    "    str     x8, [sp, #0x8]\n"
    "    bl      _ZNK4sead14SafeStringBaseIcE9findIndexERKS1_\n"
    "    cmn     w0, #0x1\n"
    "    b.eq    .L_sub_710064EF24_64f008\n"
    ".L_sub_710064EF24_64efac:\n"
    "    ldrb    w8, [x21, #0xa]\n"
    "    cmp     w8, #0xff\n"
    "    b.eq    .L_sub_710064EF24_64efc8\n"
    "    mov     x0, x23\n"
    "    mov     x1, x19\n"
    "    bl      _ZN4ksys3map16AutoPlacementMgr6auto11ERKN4sead7Vector3IfEE\n"
    "    tbnz    w0, #0x0, .L_sub_710064EF24_64f008\n"
    ".L_sub_710064EF24_64efc8:\n"
    "    mov     x0, x21\n"
    "    mov     x1, x20\n"
    "    mov     w2, w22\n"
    "    mov     x3, x19\n"
    "    bl      "
    "_ZN4ksys3map13AutoPlacement14sub_710064E178ERKN4sead14SafeStringBaseIcEEjRKNS2_7Vector3IfEE\n"
    "    tbz     w0, #0x0, .L_sub_710064EF24_64f008\n"
    "    ldrb    w8, [x21, #0xa]\n"
    "    cmp     w8, #0xfd\n"
    "    b.ls    .L_sub_710064EF24_64eff4\n"
    "    orr     w0, wzr, #0x1\n"
    "    b       .L_sub_710064EF24_64f00c\n"
    ".L_sub_710064EF24_64eff4:\n"
    "    ldr     x0, [x24]\n"
    "    mov     x1, x20\n"
    "    mov     x2, x19\n"
    "    bl      "
    "_ZN4ksys3map16AutoPlacementMgr5auto2ERKN4sead14SafeStringBaseIcEERKNS2_7Vector3IfEE\n"
    "    tbz     w0, #0x0, .L_sub_710064EF24_64f024\n"
    ".L_sub_710064EF24_64f008:\n"
    "    mov     w0, wzr\n"
    ".L_sub_710064EF24_64f00c:\n"
    "    ldp     x29, x30, [sp, #0x40]\n"
    "    ldp     x20, x19, [sp, #0x30]\n"
    "    ldp     x22, x21, [sp, #0x20]\n"
    "    ldp     x24, x23, [sp, #0x10]\n"
    "    add     sp, sp, #0x50\n"
    "    ret\n"
    ".L_sub_710064EF24_64f024:\n"
    "    orr     w0, wzr, #0x1\n"
    "    b       .L_sub_710064EF24_64f00c\n"
    ".size _ZN4ksys3map13AutoPlacement14sub_710064EF24EPNS0_14ActorSpawnInfoERKN4sead7Vector3IfEE, "
    ". - _ZN4ksys3map13AutoPlacement14sub_710064EF24EPNS0_14ActorSpawnInfoERKN4sead7Vector3IfEE\n"
    ".section .rodata\n"
    ".L_sub_710064EF24_dragon:\n"
    "    .string \"Enemy_Dragon\"\n"
    ".text\n");
#else
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
#endif

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

    mThing = &mThing2;
    _6 = 0;
    _b = 0xFF;

    auto& grp = mGroups[mGroupIdx];
    if (grp.a.isEmpty()) {
        return -1;
    }

    _8868 = sead::SafeString::cEmptyString;
    alignas(8) s16 tmp = 0;
    res->start(this, grp.a.cstr(), &tmp);
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
        mRaycast = phys::RayCastForRequest::allocRequest(nullptr, phys::GroundHit::Animal);
        next = mRaycast != nullptr ? State::Initialized : State::Invalid;
        break;
    case State::LayersDone:
        mRaycast->submitRequest(phys::ContactLayerType::Entity);
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

#ifdef MATCHING_HACK_NX_CLANG
    bool has_tag = act::hasTag(actor, act::tags::Tree);
    if (!has_tag)
        has_tag = act::hasTag(actor, act::tags::AutoPlacementForbidCreate);
    asm volatile("" : "+r"(has_tag));
    mNearFlag.set(has_tag);
#else
    mNearFlag.set(act::hasTag(actor, act::tags::Tree) ||
                  act::hasTag(actor, act::tags::AutoPlacementForbidCreate));
#endif

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

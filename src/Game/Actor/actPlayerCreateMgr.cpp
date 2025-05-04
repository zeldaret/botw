#include "Game/Actor/actPlayerCreateMgr.h"
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadStringBuilder.h>
#include "Game/Actor/actPlayerCreateUtils.h"
#include "Game/Actor/actWeapon.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actInfoCommon.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::act {

void PlayerCreateDebugStub::init() {
    struct MsgStub {
        sead::SafeString msg;
        u64 unused{};
    } stub{};
    stub.msg = "読み込み中デバッグボード";  // Loading Debug Board
    _0 = 3;
    mDebugStatus = "◎読み込み中◎";  // Loading
    _18 = 0.9;
    _1c = 0;
    mColor20 = {1.0f, 1.0f, 1.0f, 1.0f};
    mColor30 = {0.2f, 0.2f, 0.2f, 1.0f};
    _40.set(1.8, 0);
    _48.set(198.638428, 34.742115);
    mColor50 = {0.0f, 0.8f, 0.8f, 0.3f};
    _60 = 0;
    _68 = 0;
    _70 = 0;
    _78 = {-506.679992, -256.519989, 0};
    mColor84 = {0.0f, 0.0f, 0.0f, 1.0f};
}

SEAD_SINGLETON_DISPOSER_IMPL(CreatePlayerEquipActorMgr)

CreatePlayerEquipActorMgr::CreatePlayerEquipActorMgr() {
    mTracer.init("CreatePlayerEquipActorMgr");
}

CreatePlayerEquipActorMgr::~CreatePlayerEquipActorMgr() {
    mTracer.finish();
}

void CreatePlayerEquipActorMgr::init() {
    mDebugStub.init();
}

// NON_MATCHING single reorder
void CreatePlayerEquipActorMgr::postCalc() {
    if (mIsLoading.isZero()) {
        // nothing is loading
        return;
    }
    auto* handle = &mProcHandles[0];
    for (s32 i = 0; i < (s32)CreateEquipmentSlot::Length; ++i, ++handle) {
        if (!isSlotLoading(i)) {
            continue;
        }
        if (handle->hasProcCreationFailed()) {
            handle->isProcCreationCancelled();
            handle->deleteProc();
            mEntries[i].reset();
            mIsLoading.resetBit(i);
            continue;
        }

        if (handle->isProcReady()) {
            if (isArmorCreateEquipmentSlot(i)) {
                auto* actor = sead::DynamicCast<ksys::act::Actor>(handle->releaseAndWakeProc());
                mEntries[i].mProcLink.acquire(actor, false);
            }
            mEntries[i].mStatus = EntryStatus::Ready;
        }
    }
}

void CreatePlayerEquipActorMgr::resetAll() {
    for (s32 i = 0; i < (s32)CreateEquipmentSlot::Length; ++i) {
        reset(i);
    }
    mIsLoading.makeAllZero();
}

void CreatePlayerEquipActorMgr::reset(s32 slot_idx) {
    auto& handle = mProcHandles[slot_idx];
    if (handle.isAllocatedOrFailed()) {
        handle.deleteProc();
    }
    mIsLoading.resetBit(slot_idx);
    mEntries[slot_idx].reset();
}

bool CreatePlayerEquipActorMgr::areAllWeaponActorsReady() const {
    if (mIsLoading.isZero()) {
        return true;
    }
    auto* handle = &mProcHandles[0];
    for (u32 i = 0; i < (u32)CreateEquipmentSlot::Length; ++i, ++handle) {
        if (isSlotLoading((s32)i)) {
            return false;
        }
        auto* weapon = sead::DynamicCast<ksys::act::WeaponBase>(handle->getProc());
        if (weapon && !weapon->areExtraActorsReady()) {
            return false;
        }
    }
    return true;
}

bool CreatePlayerEquipActorMgr::isEquipmentProcReady(s32 slot_idx) const {
    const auto& entry = mEntries[slot_idx];
    if (entry.mStatus != EntryStatus::Ready) {
        return false;
    }
    const auto& handle = mProcHandles[slot_idx];
    if (handle.isAllocatedOrFailed()) {
        return handle.isProcReady();
    }
    return false;
}

ksys::act::Actor* CreatePlayerEquipActorMgr::tryGetEquipmentActor(s32 slot_idx) {
    if (mEntries[slot_idx].mStatus != EntryStatus::Ready) {
        return nullptr;
    }
    auto& handle = mProcHandles[slot_idx];
    if (handle.isAllocatedOrFailed()) {
        if (handle.isProcReady()) {
            auto* actor = sead::DynamicCast<ksys::act::Actor>(handle.releaseAndWakeProc());
            mEntries[slot_idx].mProcLink.acquire(actor, false);
        }
    }

    auto* actor =
        sead::DynamicCast<ksys::act::Actor>(mEntries[slot_idx].mProcLink.getProc(nullptr, nullptr));

    mEntries[slot_idx].reset();

    return actor;
}

void CreatePlayerEquipActorMgr::requestCreateWeapon(s32 slot_idx, const sead::SafeString& name,
                                                    int value, const WeaponModifierInfo* modifier,
                                                    const sead::SafeString& caller) {
    auto scope = mTracer.trace()->makeScope("requestCreateWeapon", caller, 1);

    deleteLoadingProc(slot_idx);
    auto* player = ksys::act::PlayerInfo::instance()->getPlayer();

    sead::Matrix34f pos;
    pos.makeT(player->getMtx().getTranslation());

    requestCreateWeaponByRawLife(name.cstr(), pos, 1.0,
                                 ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(),
                                 &mProcHandles[slot_idx], value, false, modifier, 2, 2);

    onSlotLoadingRequested(slot_idx, name);
}

void CreatePlayerEquipActorMgr::requestCreateWeapon(const sead::SafeString& name, int value,
                                                    const WeaponModifierInfo* modifier,
                                                    const sead::SafeString& caller) {
    auto scope = mTracer.trace()->makeScope("requestCreateWeapon", caller, 1);
    auto* info_data = ksys::act::InfoData::instance();
    if (!info_data) {
        return;
    }
    const char* profile_raw;
    if (!info_data->getActorProfile(&profile_raw, name.cstr())) {
        return;
    }
    sead::SafeString profile = profile_raw;
    auto slot = CreateEquipmentSlot::WeaponSword;
    if (profile == "WeaponBow") {
        slot = CreateEquipmentSlot::WeaponBow;
    } else if (profile == "WeaponShield") {
        slot = CreateEquipmentSlot::WeaponShield;
    }

    requestCreateWeapon((s32)slot, name, value, modifier, caller);
}

// TODO: initialized in sInitArmorStrings (0x7100E2D0F0)
// find a better place to put these
// NOLINTNEXTLINE(misc-use-internal-linkage) doesn't match with static
sead::SafeString ArmorDyeColor;  // "ArmorDyeColor"
// NOLINTNEXTLINE(misc-use-internal-linkage) doesn't match with static
sead::SafeString EnableDynamicColorChange;  // "EnableDynamicColorChange"

void CreatePlayerEquipActorMgr::requestCreateArmor(s32 slot_idx, const sead::SafeString& name,
                                                   int dye_color, const sead::SafeString& caller) {
    auto scope = mTracer.trace()->makeScope("requestCreateArmor", caller, 1);

    deleteLoadingProc(slot_idx);

    ksys::act::InstParamPack params;
    bool is_dye = ksys::act::InfoData::instance()->hasTag(name.cstr(), ksys::act::tags::ArmorDye);
    if (is_dye) {
        params->add(dye_color, ArmorDyeColor);
        if (ksys::gdt::getFlag_ColorChange_EnablePreview()) {
            params->add(true, EnableDynamicColorChange);
        }
    }

    {
        ksys::act::ActorConstDataAccess access;
        ksys::act::acquireActor(&ksys::act::PlayerInfo::instance()->getPlayerLink(), &access);
        sead::Vector3f pos;
        access.getActorMtx().getTranslation(pos);
        params->addPosition(pos);
        params->addResourceLane(2);
        ksys::act::ActorCreator::instance()->requestCreateActor(
            name.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(),
            &mProcHandles[slot_idx], &params, nullptr, 2);
    }

    onSlotLoadingRequested(slot_idx, name);
}

void CreatePlayerEquipActorMgr::requestCreateArmor(const sead::SafeString& name, int dye_color,
                                                   const sead::SafeString& caller) {
    auto scope = mTracer.trace()->makeScope("requestCreateArmor", caller, 1);
    auto* info_data = ksys::act::InfoData::instance();
    if (!info_data) {
        return;
    }
    const char* profile_raw;
    if (!info_data->getActorProfile(&profile_raw, name.cstr())) {
        return;
    }

    sead::SafeString profile = profile_raw;
    auto slot = CreateEquipmentSlot::ArmorHead;
    if (profile == "Armor_Upper") {
        slot = CreateEquipmentSlot::ArmorUpper;
    } else if (profile == "Armor_Lower") {
        slot = CreateEquipmentSlot::ArmorLower;
    }

    requestCreateArmor((s32)slot, name, dye_color, caller);
}

void CreatePlayerEquipActorMgr::requestCreateDefaultArmor(s32 slot,
                                                          const sead::SafeString& caller) {
    switch (slot) {
    case (s32)CreateEquipmentSlot::ArmorHead:
        requestCreateArmor(slot, "Armor_Default_Head", -1, caller);
        break;
    case (s32)CreateEquipmentSlot::ArmorUpper:
        requestCreateArmor(slot, "Armor_Default_Upper", -1, caller);
        break;
    case (s32)CreateEquipmentSlot::ArmorLower:
        requestCreateArmor(slot, "Armor_Default_Lower", -1, caller);
        break;
    default:
        break;
    }
}

void CreatePlayerEquipActorMgr::requestCreateArmorHeadB(const sead::SafeString& name, int dye_color,
                                                        const sead::SafeString& caller) {
    sead::FixedStringBuilder<0x40> s;
    s.copy(name.cstr());
    s.append("_B", -1);
    requestCreateArmor((s32)CreateEquipmentSlot::ArmorHead, s, dye_color, caller);
}

bool CreatePlayerEquipActorMgr::isSlotLoading(s32 slot_idx) const {
    return mIsLoading.isOnBit(slot_idx) && mEntries[slot_idx].mStatus == EntryStatus::Loading;
}

void CreatePlayerEquipActorMgr::deleteLoadingProc(s32 slot_idx) {
    if (mIsLoading.isOnBit(slot_idx)) {
        mProcHandles[slot_idx].deleteProc();
    }
}

void CreatePlayerEquipActorMgr::onSlotLoadingRequested(s32 slot_idx, const sead::SafeString& name) {
    if (mProcHandles[slot_idx].isAllocatedOrFailed()) {
        auto& entry = mEntries[slot_idx];
        entry.mActorName.copy(name.cstr());
        mIsLoading.setBit(slot_idx);
        entry.mStatus = EntryStatus::Loading;
    }
}

bool needsArmorHeadB(const sead::SafeString& armor_head_name,
                     const sead::SafeString& armor_upper_name) {
    if (armor_upper_name.isEmpty()) {
        return false;
    }
    return isArmorHeadMantleType2(armor_head_name) &&
           isArmorUpperNotUseMantleType0(armor_upper_name);
}

bool isArmorHeadMantleType2(const sead::SafeString& armor_head_name) {
    if (!ksys::act::InfoData::instance()) {
        return false;
    }
    return ksys::act::getArmorHeadMantleType(ksys::act::InfoData::instance(),
                                             armor_head_name.cstr()) == 2;
}

bool isArmorUpperNotUseMantleType0(const sead::SafeString& armor_upper_name) {
    if (!ksys::act::InfoData::instance()) {
        return false;
    }
    return ksys::act::getArmorUpperUseMantleType(ksys::act::InfoData::instance(),
                                                 armor_upper_name.cstr()) != 0;
}

}  // namespace uking::act

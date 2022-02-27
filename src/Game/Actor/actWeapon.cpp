#include "Game/Actor/actWeapon.h"
#include <random/seadGlobalRandom.h>
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actGlobalParameter.h"
#include "KingSystem/ActorSystem/actInfoCommon.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGlobal.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectWeaponCommon.h"
#include "KingSystem/Utils/Byaml/Byaml.h"

namespace uking::act {

WeaponModifierInfo::WeaponModifierInfo(const ui::PouchItem& item) {
    fromItem(item);
}

void WeaponModifierInfo::fromItem(const ui::PouchItem& item) {
    if (item.getType() <= ui::PouchItemType::Shield) {
        set(item.getWeaponData().mAddType, item.getWeaponData().mAddValue);
    } else {
        flags.setDirect(0);
        value = 0;
    }
}

int WeaponModifierInfo::getAddLife() const {
    if (flags.isOff(WeaponModifier::AddLife))
        return 0;
    return getLifeMultiplier() * value;
}

int WeaponModifierInfo::getLifeMultiplier() {
    return 100;
}

void WeaponModifierInfo::loadPorchSwordFlag(int idx) {
    set(ksys::gdt::getFlag_PorchSword_FlagSp(idx), ksys::gdt::getFlag_PorchSword_ValueSp(idx));
}

void WeaponModifierInfo::loadPorchShieldFlag(int idx) {
    set(ksys::gdt::getFlag_PorchShield_FlagSp(idx), ksys::gdt::getFlag_PorchShield_ValueSp(idx));
}

void WeaponModifierInfo::loadPorchBowFlag(int idx) {
    set(ksys::gdt::getFlag_PorchBow_FlagSp(idx), ksys::gdt::getFlag_PorchBow_ValueSp(idx));
}

void WeaponModifierInfo::savePorchSwordFlag(int idx) const {
    ksys::gdt::setFlag_PorchSword_FlagSp(flags.getDirect(), idx);
    ksys::gdt::setFlag_PorchSword_ValueSp(value, idx);
}

void WeaponModifierInfo::savePorchShieldFlag(int idx) const {
    ksys::gdt::setFlag_PorchShield_FlagSp(flags.getDirect(), idx);
    ksys::gdt::setFlag_PorchShield_ValueSp(value, idx);
}

void WeaponModifierInfo::savePorchBowFlag(int idx) const {
    ksys::gdt::setFlag_PorchBow_FlagSp(flags.getDirect(), idx);
    ksys::gdt::setFlag_PorchBow_ValueSp(value, idx);
}

void WeaponModifierInfo::loadEquipStandSwordFlag(int idx) {
    set(ksys::gdt::getFlag_EquipStandSword_FlagSp(idx),
        ksys::gdt::getFlag_EquipStandSword_ValueSp(idx));
}

void WeaponModifierInfo::loadEquipStandShieldFlag(int idx) {
    set(ksys::gdt::getFlag_EquipStandShield_FlagSp(idx),
        ksys::gdt::getFlag_EquipStandShield_ValueSp(idx));
}

void WeaponModifierInfo::loadEquipStandBowFlag(int idx) {
    set(ksys::gdt::getFlag_EquipStandBow_FlagSp(idx),
        ksys::gdt::getFlag_EquipStandBow_ValueSp(idx));
}

void WeaponModifierInfo::saveEquipStandSwordFlag(int idx) const {
    ksys::gdt::setFlag_EquipStandSword_FlagSp(flags.getDirect(), idx);
    ksys::gdt::setFlag_EquipStandSword_ValueSp(value, idx);
}

void WeaponModifierInfo::saveEquipStandShieldFlag(int idx) const {
    ksys::gdt::setFlag_EquipStandShield_FlagSp(flags.getDirect(), idx);
    ksys::gdt::setFlag_EquipStandShield_ValueSp(value, idx);
}

void WeaponModifierInfo::saveEquipStandBowFlag(int idx) const {
    ksys::gdt::setFlag_EquipStandBow_FlagSp(flags.getDirect(), idx);
    ksys::gdt::setFlag_EquipStandBow_ValueSp(value, idx);
}

void WeaponModifierInfo::addModifierParams(ksys::act::InstParamPack& params) const {
    params->add(value, "AddParam");
    params->add(int(flags.getDirect()), "AddSpecialFlag");
}

void WeaponModifierInfo::set(u32 type_, u32 value_) {
    flags.setDirect(type_);
    value = value_;
}

bool WeaponModifierRanges::loadTierBlue(const sead::SafeString& actor) {
    auto* info = ksys::act::InfoData::instance();
    if (!info)
        return false;

    al::ByamlIter iter;
    if (!info->getActorIter(&iter, actor.cstr()))
        return false;

    addAtkMin = ksys::act::getWeaponCommonSharpWeaponAddAtkMin(iter);
    addAtkMax = ksys::act::getWeaponCommonSharpWeaponAddAtkMax(iter);

    addLifeMin = ksys::act::getWeaponCommonSharpWeaponAddLifeMin(iter);
    addLifeMax = ksys::act::getWeaponCommonSharpWeaponAddLifeMax(iter);

    addCrit = ksys::act::getWeaponCommonSharpWeaponAddCrit(iter);

    addGuardMin = ksys::act::getWeaponCommonSharpWeaponAddGuardMin(iter);
    addGuardMax = ksys::act::getWeaponCommonSharpWeaponAddGuardMax(iter);

    return true;
}

bool WeaponModifierRanges::loadTierYellow(const sead::SafeString& actor) {
    auto* info = ksys::act::InfoData::instance();
    if (!info)
        return false;

    al::ByamlIter iter;
    if (!info->getActorIter(&iter, actor.cstr()))
        return false;

    isTierYellow = true;

    addAtkMin = ksys::act::getWeaponCommonPoweredSharpAddAtkMin(iter);
    addAtkMax = ksys::act::getWeaponCommonPoweredSharpAddAtkMax(iter);

    addLifeMin = ksys::act::getWeaponCommonPoweredSharpAddLifeMin(iter);
    addLifeMax = ksys::act::getWeaponCommonPoweredSharpAddLifeMax(iter);

    addGuardMin = ksys::act::getWeaponCommonPoweredSharpWeaponAddGuardMin(iter);
    addGuardMax = ksys::act::getWeaponCommonPoweredSharpWeaponAddGuardMax(iter);

    addThrowMin = ksys::act::getWeaponCommonPoweredSharpAddThrowMin(iter);
    addThrowMax = ksys::act::getWeaponCommonPoweredSharpAddThrowMax(iter);

    addSpreadFire = ksys::act::getWeaponCommonPoweredSharpAddSpreadFire(iter);
    addZoomRapid = ksys::act::getWeaponCommonPoweredSharpAddZoomRapid(iter);

    addRapidFireMin = ksys::act::getWeaponCommonPoweredSharpAddRapidFireMin(iter);
    addRapidFireMax = ksys::act::getWeaponCommonPoweredSharpAddRapidFireMax(iter);

    addSurfMaster = ksys::act::getWeaponCommonPoweredSharpAddSurfMaster(iter);

    return true;
}

WeaponModifier WeaponModifierRanges::getRandomModifier() const {
    u32 max = 1;
    WeaponModifier modifier = WeaponModifier::None;

    if (addAtkMin > 0) {
        modifier = WeaponModifier::AddAtk;
        ++max;
    }

    if (addLifeMin > 0) {
        const u32 x = sead::GlobalRandom::instance()->getU32(max);
        if (x == 0) {
            modifier = WeaponModifier::AddLife;
            ++max;
        }
    }

    if (addCrit && sead::GlobalRandom::instance()->getU32(max) == 0) {
        modifier = WeaponModifier::AddCrit;
        ++max;
    }

    if (addGuardMin > 0 && sead::GlobalRandom::instance()->getU32(max) == 0) {
        modifier = WeaponModifier::AddGuard;
        ++max;
    }

    if ((addThrowMin != 1.0 || addThrowMax != 1.0) &&
        sead::GlobalRandom::instance()->getU32(max) == 0) {
        modifier = WeaponModifier::AddThrow;
        ++max;
    }

    if (addSpreadFire && sead::GlobalRandom::instance()->getU32(max) == 0) {
        modifier = WeaponModifier::AddSpreadFire;
        ++max;
    }

    if (addZoomRapid && sead::GlobalRandom::instance()->getU32(max) == 0) {
        modifier = WeaponModifier::AddZoomRapid;
        ++max;
    }

    if ((addRapidFireMin != 1.0 || addRapidFireMax != 1.0) &&
        sead::GlobalRandom::instance()->getU32(max) == 0) {
        modifier = WeaponModifier::AddRapidFire;
        ++max;
    }

    if (addSurfMaster && sead::GlobalRandom::instance()->getU32(max) == 0) {
        modifier = WeaponModifier::AddSurfMaster;
        ++max;
    }

    return modifier;
}

bool WeaponModifierRanges::isConfigValid() const {
    if (addAtkMin <= 0 && addLifeMin <= 0 && !addCrit && addGuardMin <= 0 && addThrowMin == 1.0 &&
        addThrowMax == 1.0 && !addSpreadFire && !addZoomRapid && addRapidFireMin == 1.0 &&
        addRapidFireMax == 1.0 && !addSurfMaster) {
        return false;
    }

    if (addAtkMin < 0 || (addAtkMin > 0 && addAtkMin > addAtkMax))
        return false;

    if (addLifeMin < 0 || (addLifeMin > 0 && addLifeMin > addLifeMax))
        return false;

    if (addThrowMin < 0.0 || (addThrowMin > 0.0 && addThrowMin > addThrowMax))
        return false;

    if (addRapidFireMin < 0.0 || (addRapidFireMin > 0.0 && addRapidFireMin > addRapidFireMax))
        return false;

    return true;
}

bool WeaponModifierInfo::pickRandomBlueModifierAmiibo(const sead::SafeString& actor) {
    if (!ksys::act::InfoData::instance())
        return false;

    WeaponModifierRanges ranges;
    if (!ranges.loadTierBlue(actor))
        return false;

    return pickRandomModifierAmiibo(ranges);
}

bool WeaponModifierInfo::pickRandomModifierAmiibo(const WeaponModifierRanges& ranges) {
    const auto modifier = ranges.getRandomModifier();
    switch (modifier) {
    case WeaponModifier::None:
        return false;
    case WeaponModifier::AddAtk:
        if (ranges.addAtkMax > 0)
            setModifier(WeaponModifier::AddAtk, ranges.addAtkMax);
        return true;
    case WeaponModifier::AddLife:
        if (ranges.addLifeMax > 0)
            setModifier(WeaponModifier::AddLife, ranges.addLifeMax);
        return true;
    case WeaponModifier::AddThrow:
        if (ranges.addThrowMax > 0.0)
            setModifierFloat(WeaponModifier::AddThrow, ranges.addThrowMax);
        return true;
    case WeaponModifier::AddSpreadFire:
        setModifier(WeaponModifier::AddSpreadFire, 5);
        return true;
    case WeaponModifier::AddRapidFire:
        if (ranges.addRapidFireMin > 0.0)
            setModifierFloat(WeaponModifier::AddRapidFire, ranges.addRapidFireMin);
        return true;
    case WeaponModifier::AddSurfMaster: {
        if (!ksys::act::GlobalParameter::instance())
            return true;
        auto* param = ksys::act::GlobalParameter::instance()->getGlobalParam();
        if (param && param->mShieldSurfMasterFrictionRatio.ref() > 0.0) {
            setModifierFloat(WeaponModifier::AddSurfMaster,
                             param->mShieldSurfMasterFrictionRatio.ref());
        }
        return true;
    }
    case WeaponModifier::AddGuard:
        if (ranges.addGuardMax > 0) {
            /// @bug This is supposed to be WeaponModifier::AddGuard.
            setModifier(WeaponModifier::AddLife, ranges.addGuardMax);
        }
        return true;
    default:
        flags = modifier;
        value = 0;
        return true;
    }
}

bool WeaponModifierInfo::pickRandomYellowModifierAmiibo(const sead::SafeString& actor) {
    if (!ksys::act::InfoData::instance())
        return false;

    WeaponModifierRanges ranges;
    if (!ranges.loadTierYellow(actor))
        return false;

    return pickRandomModifierAmiibo(ranges);
}

// NON_MATCHING: isConfigValid() somehow does not match when inlined (but matches the Wii U version)
bool WeaponModifierInfo::pickRandomBlueModifierTbox(const sead::SafeString& actor) {
    auto* info = ksys::act::InfoData::instance();
    if (!info)
        return false;

    al::ByamlIter iter;
    if (!info->getActorIter(&iter, actor.cstr()))
        return false;

    WeaponModifierRanges ranges;
    if (!ranges.loadTierBlue(actor))
        return false;

    if (!ranges.isConfigValid())
        return false;

    return pickRandomModifier(ranges);
}

bool WeaponModifierInfo::pickRandomModifier(const WeaponModifierRanges& ranges) {
    const auto modifier = ranges.getRandomModifier();
    if (modifier == WeaponModifier::None)
        return false;

    if (ranges.isTierYellow)
        flags.set(WeaponModifier::IsYellow);

    switch (modifier) {
    case WeaponModifier::AddAtk: {
        const auto min = ranges.addAtkMin;
        const auto max = ranges.addAtkMax;
        const auto val = sead::GlobalRandom::instance()->getS32Range(min, max + 1);
        if (val > 0)
            setModifier(WeaponModifier::AddAtk, val);
        return true;
    }
    case WeaponModifier::AddLife: {
        const auto min = ranges.addLifeMin;
        const auto max = ranges.addLifeMax;
        const auto val = sead::GlobalRandom::instance()->getS32Range(min, max + 1);
        if (val > 0)
            setModifier(WeaponModifier::AddLife, val);
        return true;
    }
    case WeaponModifier::AddThrow: {
        const auto val =
            sead::GlobalRandom::instance()->getF32Range(ranges.addThrowMin, ranges.addThrowMax);
        if (val > 0)
            setModifierFloat(WeaponModifier::AddThrow, val);
        return true;
    }
    case WeaponModifier::AddSpreadFire:
        setModifier(WeaponModifier::AddSpreadFire, 5);
        return true;
    case WeaponModifier::AddRapidFire: {
        const auto val = sead::GlobalRandom::instance()->getF32Range(ranges.addRapidFireMin,
                                                                     ranges.addRapidFireMax);
        if (val > 0)
            setModifierFloat(WeaponModifier::AddRapidFire, val);
        return true;
    }
    case WeaponModifier::AddSurfMaster: {
        if (!ksys::act::GlobalParameter::instance())
            return true;
        auto* param = ksys::act::GlobalParameter::instance()->getGlobalParam();
        if (param && param->mShieldSurfMasterFrictionRatio.ref() > 0.0) {
            setModifierFloat(WeaponModifier::AddSurfMaster,
                             param->mShieldSurfMasterFrictionRatio.ref());
        }
        return true;
    }
    case WeaponModifier::AddGuard: {
        const auto min = ranges.addGuardMin;
        const auto max = ranges.addGuardMax;
        const auto val = sead::GlobalRandom::instance()->getS32Range(min, max + 1);
        if (val > 0)
            setModifier(WeaponModifier::AddGuard, val);
        return true;
    }
    default:
        flags = modifier;
        value = 0;
        return true;
    }
}

bool WeaponModifierRanges::loadTierBlue(const ksys::res::GParamList& gparamlist) {
    const auto* param = gparamlist.getWeaponCommon();
    addAtkMin = param->mSharpWeaponAddAtkMin.ref();
    addAtkMax = param->mSharpWeaponAddAtkMax.ref();
    addLifeMin = param->mSharpWeaponAddLifeMin.ref();
    addLifeMax = param->mSharpWeaponAddLifeMax.ref();
    addCrit = param->mSharpWeaponAddCrit.ref();
    addGuardMin = param->mSharpWeaponAddGuardMin.ref();
    addGuardMax = param->mSharpWeaponAddGuardMax.ref();
    return true;
}

// NON_MATCHING: isConfigValid() somehow does not match when inlined (but matches the Wii U version)
bool WeaponModifierInfo::pickRandomBlueModifierActor(const ksys::act::ActorConstDataAccess& acc) {
    WeaponModifierRanges ranges;
    const auto& gparamlist = *acc.getGParamList();
    if (ranges.loadTierBlue(gparamlist)) {
        static_cast<void>(acc.getName());
        if (ranges.isConfigValid())
            return pickRandomModifier(ranges);
    }
    return false;
}

// NON_MATCHING: isConfigValid() somehow does not match when inlined (but matches the Wii U version)
bool WeaponModifierInfo::pickRandomYellowModifierTbox(const sead::SafeString& actor) {
    auto* info = ksys::act::InfoData::instance();
    if (!info)
        return false;

    al::ByamlIter iter;
    if (!info->getActorIter(&iter, actor.cstr()))
        return false;

    WeaponModifierRanges ranges;
    if (!ranges.loadTierYellow(actor))
        return false;

    if (!ranges.isConfigValid())
        return false;

    return pickRandomModifier(ranges);
}

bool WeaponModifierRanges::loadTierYellow(const ksys::res::GParamList& gparamlist) {
    const auto* param = gparamlist.getWeaponCommon();
    isTierYellow = true;
    addAtkMin = param->mPoweredSharpAddAtkMin.ref();
    addAtkMax = param->mPoweredSharpAddAtkMax.ref();
    addLifeMin = param->mPoweredSharpAddLifeMin.ref();
    addLifeMax = param->mPoweredSharpAddLifeMax.ref();
    addGuardMin = param->mPoweredSharpWeaponAddGuardMin.ref();
    addGuardMax = param->mPoweredSharpWeaponAddGuardMax.ref();
    addThrowMin = param->mPoweredSharpAddThrowMin.ref();
    addThrowMax = param->mPoweredSharpAddThrowMax.ref();
    addSpreadFire = param->mPoweredSharpAddSpreadFire.ref();
    addZoomRapid = param->mPoweredSharpAddZoomRapid.ref();
    addRapidFireMin = param->mPoweredSharpAddRapidFireMin.ref();
    addRapidFireMax = param->mPoweredSharpAddRapidFireMax.ref();
    addSurfMaster = param->mPoweredSharpAddSurfMaster.ref();
    return true;
}

// NON_MATCHING: isConfigValid() somehow does not match when inlined (but matches the Wii U version)
bool WeaponModifierInfo::pickRandomYellowModifierActor(const ksys::act::ActorConstDataAccess& acc) {
    WeaponModifierRanges ranges;
    const auto& gparamlist = *acc.getGParamList();
    if (ranges.loadTierYellow(gparamlist)) {
        static_cast<void>(acc.getName());
        if (ranges.isConfigValid())
            return pickRandomModifier(ranges);
    }
    return false;
}

}  // namespace uking::act

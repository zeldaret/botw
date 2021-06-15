#include "Game/Damage/dmgInfoManager.h"
#include "Game/gameScene.h"
#include "KingSystem/ActorSystem/actGlobalParameter.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGlobal.h"

namespace uking::dmg {

SEAD_SINGLETON_DISPOSER_IMPL(DamageInfoMgr)

bool DamageInfoMgr::enableBoomerangRemoteBombs() {
    return false;
}

int DamageInfoMgr::getShieldRideBaseFrame() {
    auto* global = ksys::act::GlobalParameter::instance();
    if (!global || !global->getGlobalParam())
        return 0;

    return global->getGlobalParam()->mShieldRideBaseFrame.ref();
}

int DamageInfoMgr::getShieldRideHitBaseDamage() {
    auto* global = ksys::act::GlobalParameter::instance();
    if (!global || !global->getGlobalParam())
        return 0;

    return global->getGlobalParam()->mShieldRideHitBaseDamage.ref();
}

f32 DamageInfoMgr::getCriticalAttackRatio() {
    auto* global = ksys::act::GlobalParameter::instance();
    if (!global || !global->getGlobalParam())
        return 1.0;

    return global->getGlobalParam()->mCriticalAttackRatio.ref();
}

bool DamageInfoMgr::isTrueFormMasterSword() const {
    if (mMasterSwordDisableTrueForm)
        return false;

    if (ksys::gdt::getFlag_Open_MasterSword_FullPower())
        return true;

    if (ksys::gdt::getFlag_IsInHyruleCastleArea())
        return true;

    if (ksys::gdt::getFlag_LastBossGanonBeastGenerateFlag())
        return true;

    const sead::SafeString& map = GameScene::getCurrentMapName();

    if (!ksys::gdt::getFlag_Die_PGanonElectric() && map == "RemainsElectric")
        return true;

    if (!ksys::gdt::getFlag_Die_PGanonFire() && map == "RemainsFire")
        return true;

    if (!ksys::gdt::getFlag_Die_PGanonWater() && map == "RemainsWater")
        return true;

    if (!ksys::gdt::getFlag_Die_PGanonWind() && map == "RemainsWind")
        return true;

    return mMasterSwordDetectedEvil;
}

}  // namespace uking::dmg

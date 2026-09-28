#include "Game/Actor/Player/actPlayerInfo.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actBaseProc.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/ksys.h"

namespace uking::act {

SEAD_SINGLETON_DISPOSER_IMPL(PlayerInfo)

PlayerInfo::PlayerInfo() = default;
PlayerInfo::~PlayerInfo() = default;

bool PlayerInfo::init() {
    return true;
}

void PlayerInfo::resetPlayer(PlayerBase* player) {
    if (mPlayerActor == player) {
        mPlayerActor = nullptr;
        ksys::setPlayerLink(nullptr);
    }
}

bool PlayerInfo::acquireHorse(ksys::act::BaseProc* horse) {
    return mHorseLink.acquire(horse, false);
}

void PlayerInfo::setHorseLink(const ksys::act::BaseProcLink& horse_link) {
    mHorseLink = horse_link;
}

PlayerBase* PlayerInfo::getPlayer() const {
    if (!mPlayerActor) {
        return nullptr;
    }
    ksys::act::BaseProcMgr::instance()->isAccessingProcSafe(mPlayerActor, nullptr);
    return mPlayerActor;
}

PlayerBase* PlayerInfo::getPlayer_() const {
    if (!mPlayerActor) {
        return nullptr;
    }
    ksys::act::BaseProcMgr::instance()->isAccessingProcSafe(mPlayerActor, nullptr);
    return mPlayerActor;
}

s32 PlayerInfo::getMaxLifeFromPlayerActor() const {
    return mPlayerActor ? mPlayerActor->getMaxLife() : 0;
}

void PlayerInfo::setMaxHeartValue(s32 quarter_hearts) {
    ksys::gdt::setFlag_MaxHartValue(quarter_hearts);
    mMaxHeartValue = static_cast<f32>(quarter_hearts);
}

u32 PlayerInfo::getMaxHeartValue() const {
    // Return type is unsigned, but the conversion is signed
    return static_cast<s32>(mMaxHeartValue);
}

void PlayerInfo::updateMaxHeartValueFromGameData() {
    mMaxHeartValue = static_cast<f32>(ksys::gdt::getFlag_MaxHartValue());
}

void PlayerInfo::setLifeForPlayerActor(s32 life) {
    if (mPlayerActor) {
        *mPlayerActor->getLife() = life;
    }
}

s32 PlayerInfo::getLifeFromPlayerActor() const {
    if (!mPlayerActor) {
        return 0;
    }
    auto* life = mPlayerActor->getLife();
    return life ? *life : 1;
}

void PlayerInfo::recoverLife() {
    setLifeForPlayerActor(getMaxLifeFromPlayerActor());
}

void PlayerInfo::setStaminaCurrentMax(f32 max_stamina) {
    ksys::gdt::setFlag_StaminaCurrentMax(max_stamina);
    mStaminaCurrentMax = max_stamina;
}

f32 PlayerInfo::getStaminaCurrentMax() const {
    return mStaminaCurrentMax;
}

void PlayerInfo::updateStaminaCurrentMaxFromGameData() {
    mStaminaCurrentMax = ksys::gdt::getFlag_StaminaCurrentMax();
}

void PlayerInfo::setStaminaMax(f32 max_stamina) {
    ksys::gdt::setFlag_StaminaMax(max_stamina);
    mStaminaMax = max_stamina;
}

f32 PlayerInfo::getStaminaMax() const {
    return mStaminaMax;
}

void PlayerInfo::updateStaminaMaxFromGameData() {
    mStaminaMax = ksys::gdt::getFlag_StaminaMax();
}

PlayerBase* PlayerInfo::getPlayerUnchecked() {
    return mPlayerActor;
}

sead::Vector3f& PlayerInfo::getPlayerPos() {
    ksys::act::ActorConstDataAccess accessor;

    ksys::act::acquireActor(&mPlayerLink, &accessor);
    accessor.debugLog(1, "getPlayerPos");
    return mPlayerPos;
}

sead::Vector3f& PlayerInfo::getPlayerPosForPostCalc() {
    ksys::act::ActorConstDataAccess accessor;

    ksys::act::acquireActor(&mPlayerLink, &accessor);
    accessor.debugLog(0, "getPlayerPosForPostCalc");
    return mPlayerPosForPostCalc;
}

}  // namespace uking::act

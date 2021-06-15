#include "Game/Damage/dmgDamageManagerBase.h"
#include "Game/DLC/aocHardModeManager.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actLifeRecoveryInfo.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGeneral.h"

namespace uking::dmg {

DamageManagerBase_UnknownBase1::DamageManagerBase_UnknownBase1(ksys::act::Actor* actor)
    : mActor(actor) {}

// Compiler seems to combine zero(0) writes to (0x0 ,0x8) and (0x10, 0x18)
// when writing the vtable and Actor.
// The original Compiler writes (0x8, 0x10) in one 'stp', and writes 0x0 and 0x18 individually with
// 'str'. The rest seems to fall out of sync due to that, but it's otherwise functionally the same.
// NON_MATCHING: Incorrect order.
DamageManagerBase::DamageManagerBase(ksys::act::Actor* actor)
    : DamageManagerBase_UnknownBase1(actor) {}

u32 DamageManagerBase::getDamage() {
    u32 result;
    if (canTakeDamage())
        result = mDamage;
    else
        result = 0LL;

    return result;
}

void DamageManagerBase::addDamageCallback(s32 eventId, DamageCallback* callback) {
    if (mCallbacks.isBufferReady() && !callback->mDamageManager) {
        DamageCallback* next = mCallbacks[eventId];
        if (next) {
            DamageCallback* prev;
            while (next) {
                prev = next;
                next = next->mNext;
            }

            prev->mNext = callback;
            callback->mPrev = prev;
        } else {
            mCallbacks[eventId] = callback;
        }

        callback->mDamageManager = this;
        callback->mEventId = eventId;
    }
}

void DamageManagerBase::removeDamageCallback(DamageCallback* callback) {
    if (!mCallbacks.isBufferReady() || callback->mDamageManager != this) {
        return;
    }

    u32 event_id = callback->mEventId;
    DamageCallback* current_callback = mCallbacks[event_id];
    if (!current_callback) {
        if (mActor) {
            // Logging about trying to remove missing callback?
            mActor->nullsub_4649();
        }

        callback->mDamageManager = nullptr;
        callback->mEventId = -1;
#ifdef MATCHING_HACK_NX_CLANG
        asm("");  // Stop optimizing with the other clear below
#endif
        return;
    }

    if (current_callback == callback) {
        mCallbacks[event_id] = callback->mNext;
        current_callback = mCallbacks[event_id];
        if (current_callback) {
            current_callback->mPrev = nullptr;
        }
#ifdef MATCHING_HACK_NX_CLANG
        asm("");  // Stop re-using variables, generating an extra register
#endif
    } else {
        do {
            if (current_callback == callback) {
                DamageCallback* prev = callback->mPrev;
                if (prev) {
                    prev->mNext = callback->mNext;
                }
                DamageCallback* next = callback->mNext;
                if (next) {
                    next->mPrev = callback->mPrev;
                }
            }
            current_callback = current_callback->mNext;
        } while (current_callback);
    }
    callback->mNext = nullptr;
#ifdef MATCHING_HACK_NX_CLANG
    asm("");  // Stop combining the mNext and mDamageManager
#endif
    callback->mDamageManager = nullptr;
    callback->mEventId = -1;
    callback->mPrev = nullptr;
}

bool DamageManagerBase::applyDamage(s32& life) {
    auto* param_list = mActor->getParam()->getRes().mGParamList;

    const ksys::res::GParamListObjectGeneral& params = *param_list->getGeneral();
    if (params.mIsLifeInfinite.ref()) {
        // Since life is infinite, we don't need to modify the damage or life.
        // But we still call the "callback" as if damage was done.
        onApplyDamage();
        return false;
    }

    s32 damage = getDamage();
    if (damage >= 1) {
        if (ksys::act::isPlayerProfile(mActor)) {
            if (getAttacker()->hasProc()) {
                tryBuffDamage(damage);
            }
        }
    }

    tryApplyDamageRecovery(damage);

    // Actually deal damage
    onApplyDamage();
    f32 old_life = life;
    life = std::max(0, life - damage);
    bool did_damage = old_life != life;

    return did_damage;
}

void DamageManagerBase::tryBuffDamage(s32& damage) {
    if (!aoc::HardModeManager::instance()) {
        return;
    }

    if (!aoc::HardModeManager::instance()->checkFlag(aoc::HardModeManager::Flag::EnableHardMode)) {
        return;
    }

    if (!aoc::HardModeManager::instance()->isHardModeChangeOn(
            aoc::HardModeManager::HardModeChange::ApplyDamageMultiplier)) {
        return;
    }

    ksys::act::ActorConstDataAccess acc;
    ksys::act::acquireActor(getAttacker(), &acc);
    if (aoc::HardModeManager::shouldApplyMasterModeDamageMultiplier(acc)) {
        aoc::HardModeManager::buffDamage(damage);
    }
}

void DamageManagerBase::tryApplyDamageRecovery(s32& damage) {
    if (!aoc::HardModeManager::instance()) {
        return;
    }

    if (!aoc::HardModeManager::instance()->checkFlag(aoc::HardModeManager::Flag::EnableHardMode)) {
        return;
    }

    if (!aoc::HardModeManager::instance()->isHardModeChangeOn(
            uking::aoc::HardModeManager::HardModeChange::EnableLifeRegen)) {
        return;
    }

    if (!mActor->getLifeRecoverInfo()) {
        return;
    }

    // Take damage from extra HP1, and modify damage.
    // Returns true if damage remains? No more regen?
    ksys::act::LifeRecoverInfo* life_recovery_info = mActor->getLifeRecoverInfo();
    if (life_recovery_info->onApplyDamage(damage)) {
        // Update flags and counter.
        life_recovery_info->onApplyDamage_0();
    }
}

s32 DamageManagerBase::getNumCallbacks() {
    // More like number of supported event types, than number of callbacks.
    // These seem to return a fixed number for each different DamageManager class.
    return 0;
}

bool DamageManagerBase::initCallbacks(sead::Heap*) {
    // Does nothing in the Base class, and doesn't seem like any of the known classes actually
    // override this yet.
    return true;
}

bool DamageManagerBase::allocStruct20(sead::Heap* heap) {
    mStruct20_a = new (heap) Struct20;
    if (!mStruct20_a) {
        return false;
    }

    mStruct20_b = new (heap) Struct20;
    return mStruct20_b != nullptr;
}

void DamageManagerBase::preDelete1() {
    if (mStruct20_a) {
        delete mStruct20_a;
        mStruct20_a = nullptr;
    }
    if (mStruct20_b) {
        delete mStruct20_b;
        mStruct20_b = nullptr;
    }
}

bool DamageManagerBase::canTakeDamage() {
    u32 damageTypeMaybe = m49(getField50());
    if (!DamageInfoMgr::instance()) {
        return false;
    }

    s32 idx = mDamageReactionTableStuff;
    if (idx < 0) {
        return false;
    }

    if (!DamageInfoMgr::instance()->getDamagesArray().isBufferReady()) {
        return false;
    }

    DamageInfoMgr::DamageItem& item = DamageInfoMgr::instance()->getDamagesArray()[idx];
    return item.mCanTakeDamageFromType[damageTypeMaybe] & 0x1;
}

void DamageManagerBase::handleDamageForPlayer(u32* a2, u32* a3, u32* a4, u32* a5, u32* a6) {
    Struct20* currentStruct = sead::DynamicCast<Struct20>(mStruct20_b);
    if (!currentStruct) {
        return;
    }

    *a2 = currentStruct->mField_8;
    *a3 = currentStruct->mField_C;
    *a5 = currentStruct->mField_14;
    *a6 = currentStruct->mField_18;
    *a4 = currentStruct->mField_10;
}

bool DamageManagerBase::addDamage(s64, s32 damage, s32 df48, s32 minDmg, s32 f50, s32 f54,
                                  s32 f40) {
    mDamage += damage;
    mField_48 += df48;
    mMinDmg += minDmg;

    if (mField_54 >= f54) {
        return false;
    }

    mField_50 = f50;
    mField_54 = f54;
    mField_40 = f40;

    return true;
}

s32 DamageManagerBase::m49(s32 damageTypeMaybe) {
    if (damageTypeMaybe == 3) {
        return 2;
    }

    return 0;
}

}  // namespace uking::dmg

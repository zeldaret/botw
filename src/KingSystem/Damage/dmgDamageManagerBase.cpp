#include "dmgDamageManagerBase.h"
#include "Game/DLC/aoc2.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorParamMgr.h"
#include "KingSystem/ActorSystem/actLifeRecoveryInfo.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGeneral.h"
#include "KingSystem/Resource/resResourceGParamList.h"

namespace ksys::dmg {

DamageManagerBase_UnknownBase1::DamageManagerBase_UnknownBase1(ksys::act::Actor* WeaponActor)
    : mActor(WeaponActor) {}

// Compiler seems to combine zero(0) writes to (0x0 ,0x8) and (0x10, 0x18)
// when writing the vtable and Actor.
// The original Compiler writes (0x8, 0x10) in one 'stp', and writes 0x0 and 0x18 individually with
// 'str'. The rest seems to fall out of sync due to that, but it's otherwise functionally the same.
// NON_MATCHING: Incorrect order.
DamageManagerBase::DamageManagerBase(ksys::act::Actor* WeaponActor)
    : DamageManagerBase_UnknownBase1(WeaponActor) {}

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
            };

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

    u32 eventId = callback->mEventId;
    DamageCallback* currentCallback = mCallbacks[eventId];
    if (!currentCallback) {
        if (mActor) {
            // Logging about trying to remove missing callback?
            mActor->nullsub_4649();
        }

        callback->mDamageManager = NULL;
        callback->mEventId = -1;
        asm("");  // Stop optimizing with the other clear below
        return;
    }

    if (currentCallback == callback) {
        mCallbacks[eventId] = callback->mNext;
        currentCallback = mCallbacks[eventId];
        if (currentCallback) {
            currentCallback->mPrev = NULL;
        }
        asm("");  // Stop re-using variables, generating an extra register
    } else {
        do {
            if (currentCallback == callback) {
                DamageCallback* prev = callback->mPrev;
                if (prev) {
                    prev->mNext = callback->mNext;
                }
                DamageCallback* next = callback->mNext;
                if (next) {
                    next->mPrev = callback->mPrev;
                }
            }
            currentCallback = currentCallback->mNext;
        } while (currentCallback);
    }
    callback->mNext = NULL;
    asm("");  // Stop combining the mNext and mDamageManager
    callback->mDamageManager = NULL;
    callback->mEventId = -1;
    callback->mPrev = NULL;
}

bool DamageManagerBase::applyDamage(s32& life) {
    ksys::res::GParamList* paramsList;  // x8
    paramsList = mActor->mActorParam->gParamList;

    const ksys::res::GParamListObjectGeneral& params = paramsList->getGeneral();
    if (params.mIsLifeInfinite.ref()) {
        // Since life is infinite, we don't need to modify the damage or life.
        // But we still call the "callback" as if damage was done.
        onApplyDamage();
        return false;
    }

    s32 damage = getDamage();
    if (damage >= 1) {
        if (isPlayerClass(mActor)) {
            if (getAttacker()->hasProc()) {
                tryBuffDamage(damage);
            }
        }
    }

    tryApplyDamageRecovery(damage);

    // Actually deal damage
    onApplyDamage();
    f32 oldLife = life;  // Random float for some reason
    // Force positive result(Any negative result right shifted by 31 = -1, positive result = 0)
    life = (life - damage) & ~((life - damage) >> 0x1F);
    bool didDamage = oldLife != life;

    return didDamage;
}

void DamageManagerBase::tryBuffDamage(s32& damage) {
    if (!uking::aoc2::instance()) {
        return;
    }

    if (!uking::aoc2::instance()->checkFlag2(uking::aoc2::Flags2::EnableHardMode)) {
        return;
    }

    if (!uking::aoc2::instance()->checkFlag1(uking::aoc2::Flags1::ApplyDamageMultiplier)) {
        return;
    }

    ksys::act::ActorConstDataAccess acc;
    ksys::act::acquireActor(getAttacker(), &acc);
    if (uking::aoc2::shouldApplyMasterModeDamageMultiplier(acc)) {
        uking::aoc2::buffDamage(damage);
    }
}

void DamageManagerBase::tryApplyDamageRecovery(s32& damage) {
    if (!uking::aoc2::instance()) {
        return;
    }

    if (!uking::aoc2::instance()->checkFlag2(uking::aoc2::Flags2::EnableHardMode)) {
        return;
    }

    if (!uking::aoc2::instance()->checkFlag1(uking::aoc2::Flags1::EnableLifeRegen)) {
        return;
    }

    if (!mActor->getLifeRecoverInfo()) {
        return;
    }

    // Take damage from extra HP1, and modify damage.
    // Returns true if damage remains? No more regen?
    ksys::act::LifeRecoverInfo* lifeRecoveryInfo = mActor->getLifeRecoverInfo();
    if (lifeRecoveryInfo->onApplyDamage(damage)) {
        // Update flags and counter.
        lifeRecoveryInfo->onApplyDamage_0();
    }
}

s32 DamageManagerBase::getNumCallbacks() {
    // More like number of supported event types, than number of callbacks.
    // These seem to return a fixed number for each different DamageManager class.
    return 0;
}

bool DamageManagerBase::initCallbacks(sead::ExpHeap*) {
    // Does nothing in the Base class, and doesn't seem like any of the known classes actually
    // override this yet.
    return true;
}

bool DamageManagerBase::allocStruct20(sead::ExpHeap* heap) {
    mStruct20_a = new (heap, 8) Struct20;
    if (!mStruct20_a) {
        return false;
    }

    mStruct20_b = new (heap, 8) Struct20;
    return mStruct20_b != NULL;
}

void DamageManagerBase::preDelete1() {
    if (mStruct20_a) {
        delete mStruct20_a;
        mStruct20_a = NULL;
    }
    if (mStruct20_b) {
        delete mStruct20_b;
        mStruct20_b = NULL;
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

    if (!DamageInfoMgr::instance()->mDamagesArray.isBufferReady()) {
        return false;
    }

    DamageInfoMgr_DamageItem& item = DamageInfoMgr::instance()->mDamagesArray[idx];
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

}  // namespace ksys::dmg

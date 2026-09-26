#include "Game/Damage/dmgDamageMgrShield.h"

#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::dmg {

DamageMgrShield::DamageMgrShield(ksys::act::Actor* actor) : DamageMgrWeapon(actor) {
    mDamage2 = act::WeaponModifierInfo::getLifeMultiplier();
    mIsDamageType4 = false;
}

DamageMgrShield::~DamageMgrShield() = default;

void DamageMgrShield::setDamage2(f32 damage) {
    mDamage2 = act::WeaponModifierInfo::getLifeMultiplier() * damage;
}

void DamageMgrShield::m22() {
    u32 aDamage = 0;
    u32 aDf48 = 0;
    s32 a5 = -1;
    s32 a6 = -1;
    u32 aMinDmg = 0;

    if (isOwnedByPlayer()) {
        handleDamageForPlayer(&aDamage, &aDf48, &aMinDmg, &a5, &a6);
    }

    mIsDamageType4 = false;
    resetStuff();

    s32 bDamage = 0;
    s32 bDf48 = 0;
    s32 bMinDmg = 0;
    s32 b6 = -1;
    s32 b5 = -1;
    s32 b7 = 0;

    if (mField_34)
        return;

    if (isOwnedByPlayer() && shieldSurfDamageLogic(&bDamage, &bDf48, &bMinDmg, &b5, &b6, &b7) &&
        addDamage(2, bDamage, bDf48, bMinDmg, b5, b6, b7)) {
        setDamageType(2);
    }

    if (shieldDamageLogic(&bDamage, &bDf48, &bMinDmg, &b5, &b6, &b7) &&
        addDamage(3, bDamage, bDf48, bMinDmg, b5, b6, b7)) {
        setDamageType(3);
    }

    ksys::act::Chemical* chemical = mActor->getChemicalStuff();
    if (chemical && chemical->value == 3) {
        s32* life = mActor->getLife();
        bDamage = life ? *life : 1;
        bDf48 = 0;
        bMinDmg = 0;
        b5 = 9;
        b6 = 30;
        b7 = 1;
        if (addDamage(1, bDamage, bDf48, bMinDmg, b5, b6, b7))
            setDamageType(1);
    }

    if (addDamage(4, aDamage, aDf48, aMinDmg, a5, a6, 1)) {
        mIsDamageType4 = true;
        setDamageType(4);
    }

    callDamageCallbacks(0, &mDamage, &mField_48, &mMinDmg, &mField_50, &mField_54, 0);
}

s32 DamageMgrShield::getNumCallbacks() {
    return 1;
}

void DamageMgrShield::preDelete1() {
    m20();
    resetStuff();
    mCallback = nullptr;
    mIsDamageType4 = false;
}

s32 DamageMgrShield::getDamage2() {
    return mDamage2;
}

bool DamageMgrShield::isDamageType4() const {
    return mIsDamageType4;
}
}  // namespace uking::dmg

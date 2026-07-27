#pragma once

#include <basis/seadTypes.h>
#include "Game/Damage/dmgDamageManagerBase.h"

namespace uking::dmg {

class DamageMgrWeapon : public DamageManagerBase {
    SEAD_RTTI_OVERRIDE(DamageMgrWeapon, DamageManagerBase)

public:
    DamageMgrWeapon(ksys::act::Actor* actor);

    virtual void setDamage2(f32 damage);
    virtual s32 getDamage2();
    virtual s32 m52();
    virtual bool isDamageType4() const;

    void m20();
};
KSYS_CHECK_SIZE_NX150(DamageMgrWeapon, 0x68);

}  // namespace uking::dmg

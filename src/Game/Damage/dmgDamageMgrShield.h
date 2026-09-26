#pragma once

#include <basis/seadTypes.h>
#include "Game/Damage/dmgDamageMgrWeapon.h"

namespace ksys::act {
// TODO: Move Chemical to correct file
class Chemical {
public:
    char filler[0xc0];
    u8 value;
};
}  // namespace ksys::act

namespace uking::dmg {

class DamageMgrShield : public DamageMgrWeapon {
    SEAD_RTTI_OVERRIDE(DamageMgrShield, DamageMgrWeapon)

public:
    DamageMgrShield(ksys::act::Actor* actor);
    ~DamageMgrShield() override;

    void setDamage2(f32 damage) override;
    void m22() override;
    bool shieldSurfDamageLogic(s32* damage, s32* df48, s32* minDmg, s32* f50, s32* f54, s32* f40);
    bool shieldDamageLogic(s32* damage, s32* df48, s32* minDmg, s32* f50, s32* f54, s32* f40);
    s32 getNumCallbacks() override;

    void preDelete1() override;
    s32 getDamage2() override;
    bool isDamageType4() const override;

private:
    /* 0x0068 */ void* mCallback = nullptr;
    /* 0x0070 */ s32 mDamage2;
    /* 0x0074 */ bool mIsDamageType4;
};

KSYS_CHECK_SIZE_NX150(DamageMgrShield, 0x78);

}  // namespace uking::dmg

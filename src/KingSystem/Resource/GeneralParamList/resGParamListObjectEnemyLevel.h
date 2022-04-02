#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectEnemyLevel : public GParamListObject {
public:
    GParamListObjectEnemyLevel();
    const char* getName() const override { return "EnemyLevel"; }

    agl::utl::Parameter<bool> mIsAvoidDanger;
    agl::utl::Parameter<bool> mIsGuardArrow;
    agl::utl::Parameter<bool> mIsHideArrowAttack;
    agl::utl::Parameter<bool> mIsSwiftAttack;
    agl::utl::Parameter<bool> mIsBackSwiftAttack;
    agl::utl::Parameter<bool> mIsCounterAttack;
    agl::utl::Parameter<bool> mIsEscapeBomb;
    agl::utl::Parameter<bool> mIsKickBomb;
    agl::utl::Parameter<bool> mIsShootBomb;
    agl::utl::Parameter<bool> mIsThrowWeapon;
    agl::utl::Parameter<s32> mGuardPer;
    agl::utl::Parameter<bool> mIsJustGuard;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectEnemyLevel, 0x1b8);

inline GParamListObjectEnemyLevel::GParamListObjectEnemyLevel() {
    auto* const obj = &mObj;

    mIsAvoidDanger.init(false, "IsAvoidDanger", "", obj);
    mIsGuardArrow.init(false, "IsGuardArrow", "", obj);
    mIsHideArrowAttack.init(false, "IsHideArrowAttack", "", obj);
    mIsSwiftAttack.init(false, "IsSwiftAttack", "", obj);
    mIsBackSwiftAttack.init(false, "IsBackSwiftAttack", "", obj);
    mIsCounterAttack.init(false, "IsCounterAttack", "", obj);
    mIsEscapeBomb.init(false, "IsEscapeBomb", "", obj);
    mIsKickBomb.init(false, "IsKickBomb", "", obj);
    mIsShootBomb.init(false, "IsShootBomb", "", obj);
    mIsThrowWeapon.init(false, "IsThrowWeapon", "", obj);
    mGuardPer.init(0, "GuardPer", "", obj);
    mIsJustGuard.init(false, "IsJustGuard", "", obj);
}

}  // namespace ksys::res

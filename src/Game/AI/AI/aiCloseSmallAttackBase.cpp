#include "Game/AI/AI/aiCloseSmallAttackBase.h"

namespace uking::ai {

CloseSmallAttackBase::CloseSmallAttackBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CloseSmallAttackBase::~CloseSmallAttackBase() = default;

void CloseSmallAttackBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void CloseSmallAttackBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CloseSmallAttackBase::loadParams_() {
    getStaticParam(&mCloseRadius_s, "CloseRadius");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mIsIgnoreSmallHit_s, "IsIgnoreSmallHit");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai

#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CloseSmallAttackBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(CloseSmallAttackBase, ksys::act::ai::Ai)
public:
    explicit CloseSmallAttackBase(const InitArg& arg);
    ~CloseSmallAttackBase() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mCloseRadius_s{};
    // static_param at offset 0x40
    const int* mWeaponIdx_s{};
    // static_param at offset 0x48
    const bool* mIsIgnoreSmallHit_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai

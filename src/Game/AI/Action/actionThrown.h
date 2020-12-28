#pragma once

#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Thrown : public ActionEx {
    SEAD_RTTI_OVERRIDE(Thrown, ActionEx)
public:
    explicit Thrown(const InitArg& arg);
    ~Thrown() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mReactionLevel_s{};
    // static_param at offset 0x28
    const bool* mIsForceOnly_s{};
    // static_param at offset 0x30
    const bool* mIsOnImpact_s{};
    // static_param at offset 0x38
    sead::SafeString mAS_s{};
    // static_param at offset 0x48
    sead::SafeString mThrownKey_s{};
    // static_param at offset 0x58
    const sead::Vector3f* mRotSpd_s{};
    // dynamic_param at offset 0x60
    float* mPower_d{};
    // dynamic_param at offset 0x68
    bool* mIsShootByPlayer_d{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mTargetDir_d{};
};

}  // namespace uking::action

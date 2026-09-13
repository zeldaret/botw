#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LynelRodeo : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(LynelRodeo, ksys::act::ai::Action)
public:
    explicit LynelRodeo(const InitArg& arg);
    ~LynelRodeo() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mForwardSpeed_s{};
    // static_param at offset 0x28
    const float* mSideSpeed_s{};
    // static_param at offset 0x30
    const float* mRotSpeed_s{};
    // static_param at offset 0x38
    const float* mTurnCheckAngleStep_s{};
};

}  // namespace uking::action

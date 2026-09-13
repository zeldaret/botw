#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkAddLinearImpulse : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkAddLinearImpulse, ksys::act::ai::Action)
public:
    explicit ForkAddLinearImpulse(const InitArg& arg);
    ~ForkAddLinearImpulse() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mPower_s{};
    // static_param at offset 0x28
    const sead::Vector3f* mDirection_s{};
};

}  // namespace uking::action

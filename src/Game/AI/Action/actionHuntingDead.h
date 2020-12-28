#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HuntingDead : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(HuntingDead, ksys::act::ai::Action)
public:
    explicit HuntingDead(const InitArg& arg);
    ~HuntingDead() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mInWaterDepth_s{};
    // static_param at offset 0x28
    const bool* mIsUseOffsetY_s{};
    // static_param at offset 0x30
    sead::SafeString mOffsetBoneName_s{};
    // static_param at offset 0x40
    const sead::Vector3f* mExtraOffset_s{};
};

}  // namespace uking::action

#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossBowMoveForArrowRain : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SiteBossBowMoveForArrowRain, ksys::act::ai::Action)
public:
    explicit SiteBossBowMoveForArrowRain(const InitArg& arg);
    ~SiteBossBowMoveForArrowRain() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mFirstMoveSpeed_s{};
    // static_param at offset 0x28
    const float* mFirstAccelFrame_s{};
    // static_param at offset 0x30
    const float* mSecondMoveSpeed_s{};
    // static_param at offset 0x38
    const float* mSecondAccelFrame_s{};
    // static_param at offset 0x40
    sead::SafeString mASName_s{};
    // static_param at offset 0x50
    const sead::Vector3f* mMoveTarget_s{};
};

}  // namespace uking::action

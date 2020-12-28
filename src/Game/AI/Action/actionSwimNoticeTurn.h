#pragma once

#include "Game/AI/Action/actionWaterFloatBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SwimNoticeTurn : public WaterFloatBase {
    SEAD_RTTI_OVERRIDE(SwimNoticeTurn, WaterFloatBase)
public:
    explicit SwimNoticeTurn(const InitArg& arg);
    ~SwimNoticeTurn() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x60
    const float* mAngSpd_s{};
    // static_param at offset 0x68
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0x78
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action

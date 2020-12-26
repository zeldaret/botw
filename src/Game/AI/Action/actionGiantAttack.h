#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GiantAttack : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GiantAttack, ksys::act::ai::Action)
public:
    explicit GiantAttack(const InitArg& arg);
    ~GiantAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mRotSpeed_s{};
    // static_param at offset 0x28
    const float* mStopSpeedRatio_s{};
    // static_param at offset 0x30
    const float* mStopRotSpeedRatio_s{};
    // static_param at offset 0x38
    sead::SafeString mRotBaseBoneName_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action

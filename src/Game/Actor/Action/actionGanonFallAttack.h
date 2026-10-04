#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GanonFallAttack : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GanonFallAttack, ksys::act::ai::Action)
public:
    explicit GanonFallAttack(const InitArg& arg);
    ~GanonFallAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const bool* mIsEmitShockWave_s{};
    // dynamic_param at offset 0x28
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action

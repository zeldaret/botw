#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GanonThrowTornado : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GanonThrowTornado, ksys::act::ai::Action)
public:
    explicit GanonThrowTornado(const InitArg& arg);
    ~GanonThrowTornado() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mInitVelocity_s{};
    // static_param at offset 0x28
    const float* mCreateHeight_s{};
    // static_param at offset 0x30
    sead::SafeString mASName_s{};
    // static_param at offset 0x40
    const sead::Vector3f* mAppearOffset_s{};
    // dynamic_param at offset 0x48
    sead::SafeString mThrowPartsName_d{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x60
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::action

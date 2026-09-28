#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AirOctaMoveBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AirOctaMoveBase, ksys::act::ai::Action)
public:
    explicit AirOctaMoveBase(const InitArg& arg);
    ~AirOctaMoveBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mAmplitude_s{};
    // static_param at offset 0x28
    const float* mGoalDistance_s{};
    // static_param at offset 0x30
    const bool* mGoalInSuccessEnd_s{};
    // aitree_variable at offset 0x38
    void* mAirOctaDataMgr_a{};
};

}  // namespace uking::action

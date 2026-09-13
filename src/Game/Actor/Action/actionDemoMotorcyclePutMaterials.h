#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DemoMotorcyclePutMaterials : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DemoMotorcyclePutMaterials, ksys::act::ai::Action)
public:
    explicit DemoMotorcyclePutMaterials(const InitArg& arg);
    ~DemoMotorcyclePutMaterials() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mCloseSaddleFramesSincePut_s{};
    // static_param at offset 0x28
    const float* mFinishCookFramesSincePut_s{};
    // static_param at offset 0x30
    const float* mCloseSaddleFramesSincePutFairy_s{};
    // static_param at offset 0x38
    const float* mFinishCookFramesSincePutFairy_s{};
};

}  // namespace uking::action

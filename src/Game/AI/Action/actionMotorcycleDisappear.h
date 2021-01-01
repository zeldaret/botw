#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class MotorcycleDisappear : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(MotorcycleDisappear, ksys::act::ai::Action)
public:
    explicit MotorcycleDisappear(const InitArg& arg);
    ~MotorcycleDisappear() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mModelWarpEffectFrames_s{};
    // dynamic_param at offset 0x28
    sead::SafeString mDisappearEffectName_d{};
};

}  // namespace uking::action

#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Msg2CameraResetInterpolate : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(Msg2CameraResetInterpolate, ksys::act::ai::Action)
public:
    explicit Msg2CameraResetInterpolate(const InitArg& arg);
    ~Msg2CameraResetInterpolate() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic2_param at offset 0x20
    float* mInterpolateParam_d{};
};

}  // namespace uking::action

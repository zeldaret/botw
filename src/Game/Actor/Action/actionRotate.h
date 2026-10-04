#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Rotate : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(Rotate, ksys::act::ai::Action)
public:
    explicit Rotate(const InitArg& arg);
    ~Rotate() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const bool* mIsReturn_s{};
    // map_unit_param at offset 0x28
    const int* mRotAxis_m{};
    // map_unit_param at offset 0x30
    const float* mTiltAngle_m{};
    // map_unit_param at offset 0x38
    const float* mTiltAngularSpeed_m{};
};

}  // namespace uking::action

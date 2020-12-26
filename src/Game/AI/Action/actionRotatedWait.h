#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RotatedWait : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RotatedWait, ksys::act::ai::Action)
public:
    explicit RotatedWait(const InitArg& arg);
    ~RotatedWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x20
    const int* mRotAxis_m{};
    // map_unit_param at offset 0x28
    const float* mTiltAngle_m{};
};

}  // namespace uking::action

#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FixedMagneStick : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(FixedMagneStick, ksys::act::ai::Action)
public:
    explicit FixedMagneStick(const InitArg& arg);
    ~FixedMagneStick() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x20
    const float* mGrabbedMagneReleaseTime_m{};
    // aitree_variable at offset 0x28
    float* mMagneStickLength_a{};
    // aitree_variable at offset 0x30
    bool* mIsTargetFixedAcceptor_a{};
};

}  // namespace uking::action

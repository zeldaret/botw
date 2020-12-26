#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BeamMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BeamMove, ksys::act::ai::Action)
public:
    explicit BeamMove(const InitArg& arg);
    ~BeamMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mAtMinDamage_s{};
    // static_param at offset 0x28
    const int* mShieldDamage_s{};
    // static_param at offset 0x30
    const float* mForceExplodeFrame_s{};
    // aitree_variable at offset 0x38
    bool* mIsReflectThrownBullet_a{};
};

}  // namespace uking::action

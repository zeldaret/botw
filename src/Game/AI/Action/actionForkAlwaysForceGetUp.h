#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkAlwaysForceGetUp : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkAlwaysForceGetUp, ksys::act::ai::Action)
public:
    explicit ForkAlwaysForceGetUp(const InitArg& arg);
    ~ForkAlwaysForceGetUp() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // aitree_variable at offset 0x20
    void* mCRBOffsetUnit_a{};
    // static_param at offset 0x28
    const float* mRotRatio_s{};
    // static_param at offset 0x30
    const float* mRotSpdMin_s{};
    // static_param at offset 0x38
    const float* mRotSpdMax_s{};
    // static_param at offset 0x40
    const bool* mIsUseCRBOffsetUnit_s{};
};

}  // namespace uking::action

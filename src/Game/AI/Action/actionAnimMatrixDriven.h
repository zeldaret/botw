#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnimMatrixDriven : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AnimMatrixDriven, ksys::act::ai::Action)
public:
    explicit AnimMatrixDriven(const InitArg& arg);
    ~AnimMatrixDriven() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mASSlot_d{};
    // dynamic_param at offset 0x28
    int* mSequenceBank_d{};
    // dynamic_param at offset 0x30
    float* mStartFrame_d{};
    // dynamic_param at offset 0x38
    bool* mIsIgnoreSame_d{};
    // dynamic_param at offset 0x40
    bool* mIsChangeable_d{};
    // dynamic_param at offset 0x48
    sead::SafeString mASName_d{};
};

}  // namespace uking::action

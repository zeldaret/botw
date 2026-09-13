#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TakeoffFromCeilLook : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(TakeoffFromCeilLook, ksys::act::ai::Action)
public:
    explicit TakeoffFromCeilLook(const InitArg& arg);
    ~TakeoffFromCeilLook() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mDescentSpeed_s{};
    // static_param at offset 0x28
    const float* mAccRatio_s{};
    // static_param at offset 0x30
    const float* mRotSpeed_s{};
    // static_param at offset 0x38
    const float* mRotRatio_s{};
    // static_param at offset 0x40
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x48
    const float* mRotReduceRatio_s{};
};

}  // namespace uking::action

#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnmUpDownMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AnmUpDownMove, ksys::act::ai::Action)
public:
    explicit AnmUpDownMove(const InitArg& arg);
    ~AnmUpDownMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x28
    const float* mRotReduceRatio_s{};
    // static_param at offset 0x30
    const float* mAccRatio_s{};
    // static_param at offset 0x38
    sead::SafeString mASName_s{};
};

}  // namespace uking::action

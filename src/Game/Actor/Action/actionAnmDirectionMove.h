#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnmDirectionMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AnmDirectionMove, ksys::act::ai::Action)
public:
    explicit AnmDirectionMove(const InitArg& arg);
    ~AnmDirectionMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mDirection_s{};
    // static_param at offset 0x28
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x30
    const float* mRotReduceRatio_s{};
    // static_param at offset 0x38
    const bool* mIsChangeable_s{};
    // static_param at offset 0x40
    const bool* mUsereachableCheck_s{};
    // static_param at offset 0x48
    sead::SafeString mASName_s{};
};

}  // namespace uking::action

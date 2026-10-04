#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnmBackMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AnmBackMove, ksys::act::ai::Action)
public:
    explicit AnmBackMove(const InitArg& arg);
    ~AnmBackMove() override;

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
    sead::SafeString mASName_s{};
};

}  // namespace uking::action

#pragma once

#include "Game/AI/Action/actionBackWalkWithAS.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnmTimingBackWalk : public BackWalkWithAS {
    SEAD_RTTI_OVERRIDE(AnmTimingBackWalk, BackWalkWithAS)
public:
    explicit AnmTimingBackWalk(const InitArg& arg);
    ~AnmTimingBackWalk() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xd0
    const float* mAngReduceRatio_s{};
    // static_param at offset 0xd8
    const float* mPosReduceRatio_s{};
};

}  // namespace uking::action

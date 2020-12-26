#pragma once

#include "Game/AI/Action/actionAnmDrivenHoverBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnmDrivenHover : public AnmDrivenHoverBase {
    SEAD_RTTI_OVERRIDE(AnmDrivenHover, AnmDrivenHoverBase)
public:
    explicit AnmDrivenHover(const InitArg& arg);
    ~AnmDrivenHover() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x50
    const float* mRotReduceRatio_s{};
};

}  // namespace uking::action

#pragma once

#include "Game/AI/Action/actionAnmDrivenHoverBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnmDrivenHoverTurn : public AnmDrivenHoverBase {
    SEAD_RTTI_OVERRIDE(AnmDrivenHoverTurn, AnmDrivenHoverBase)
public:
    explicit AnmDrivenHoverTurn(const InitArg& arg);
    ~AnmDrivenHoverTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x50
    const float* mRotSpeed_s{};
    // static_param at offset 0x58
    const float* mBaseRotRatio_s{};
    // static_param at offset 0x60
    const float* mRotAccRatio_s{};
    // static_param at offset 0x68
    const float* mFinRotate_s{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action

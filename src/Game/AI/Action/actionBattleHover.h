#pragma once

#include "Game/AI/Action/actionHover.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BattleHover : public Hover {
    SEAD_RTTI_OVERRIDE(BattleHover, Hover)
public:
    explicit BattleHover(const InitArg& arg);
    ~BattleHover() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x70
    const float* mRotSpeed_s{};
    // dynamic_param at offset 0x78
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action

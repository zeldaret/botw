#pragma once

#include "Game/AI/Action/actionFreeMoveToTarget.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FreeMoveToTargetWithBank : public FreeMoveToTarget {
    SEAD_RTTI_OVERRIDE(FreeMoveToTargetWithBank, FreeMoveToTarget)
public:
    explicit FreeMoveToTargetWithBank(const InitArg& arg);
    ~FreeMoveToTargetWithBank() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xd0
    const float* mBankAngleMax_s{};
    // static_param at offset 0xd8
    const float* mLimitMoveAngle4Bank_s{};
};

}  // namespace uking::action

#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SeqTargetTwoAction : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SeqTargetTwoAction, ksys::act::ai::Ai)
public:
    explicit SeqTargetTwoAction(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mIsFinishedByFailAction_s{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai

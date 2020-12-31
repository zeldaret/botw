#pragma once

#include "Game/AI/AI/aiSeqTwoAction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SeqCloseDistTwoAction : public SeqTwoAction {
    SEAD_RTTI_OVERRIDE(SeqCloseDistTwoAction, SeqTwoAction)
public:
    explicit SeqCloseDistTwoAction(const InitArg& arg);
    ~SeqCloseDistTwoAction() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // static_param at offset 0x50
    const int* mWeaponIdx_s{};
    // static_param at offset 0x58
    const float* mCloseDist_s{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai

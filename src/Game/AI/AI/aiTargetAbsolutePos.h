#pragma once

#include "Game/AI/AI/aiTargetPosAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetAbsolutePos : public TargetPosAI {
    SEAD_RTTI_OVERRIDE(TargetAbsolutePos, TargetPosAI)
public:
    explicit TargetAbsolutePos(const InitArg& arg);
    ~TargetAbsolutePos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x40
    const sead::Vector3f* mTargetPos_s{};
};

}  // namespace uking::ai

#pragma once

#include "Game/AI/AI/aiTargetPosOffset.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetPosOffsetFromMyPos : public TargetPosOffset {
    SEAD_RTTI_OVERRIDE(TargetPosOffsetFromMyPos, TargetPosOffset)
public:
    explicit TargetPosOffsetFromMyPos(const InitArg& arg);
    ~TargetPosOffsetFromMyPos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x68
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai

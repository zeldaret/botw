#pragma once

#include "Game/Actor/AI/aiTargetActorPos.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class OffsetTargetPos : public TargetActorPos {
    SEAD_RTTI_OVERRIDE(OffsetTargetPos, TargetActorPos)
public:
    explicit OffsetTargetPos(const InitArg& arg);
    ~OffsetTargetPos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x40
    const int* mDir_s{};
    // static_param at offset 0x48
    const float* mOffset_s{};
    // static_param at offset 0x50
    const float* mMinDist_s{};
    // static_param at offset 0x58
    const float* mSideDist_s{};
    // static_param at offset 0x60
    const bool* mIsRandSide_s{};
};

}  // namespace uking::ai

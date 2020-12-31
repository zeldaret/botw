#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class BossBattleRoomRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(BossBattleRoomRoot, ksys::act::ai::Ai)
public:
    explicit BossBattleRoomRoot(const InitArg& arg);
    ~BossBattleRoomRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mFramesRollKeepSecond_s{};
    // static_param at offset 0x40
    const int* mNumTimesRoll_s{};
    // static_param at offset 0x48
    const float* mTitleAngle_s{};
    // static_param at offset 0x50
    const float* mRollAngle_s{};
    // static_param at offset 0x58
    const float* mFramesRotate_s{};
    // static_param at offset 0x60
    const float* mFramesReset_s{};
    // static_param at offset 0x68
    const float* mFramesRoll_s{};
    // static_param at offset 0x70
    const float* mFramesDelayRoll_s{};
    // static_param at offset 0x78
    const float* mFramesRollKeepFirst_s{};
};

}  // namespace uking::ai

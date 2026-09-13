#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PlayerLadder : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PlayerLadder, ksys::act::ai::Ai)
public:
    explicit PlayerLadder(const InitArg& arg);
    ~PlayerLadder() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // FIXME: remove this
    u8 pad_0x38[0x18];
    // static_param at offset 0x50
    const float* mLadderToClimbTime_s{};
};

}  // namespace uking::ai

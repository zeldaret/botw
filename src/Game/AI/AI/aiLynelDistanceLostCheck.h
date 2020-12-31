#pragma once

#include "Game/AI/AI/aiDistanceLostCheck.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LynelDistanceLostCheck : public DistanceLostCheck {
    SEAD_RTTI_OVERRIDE(LynelDistanceLostCheck, DistanceLostCheck)
public:
    explicit LynelDistanceLostCheck(const InitArg& arg);
    ~LynelDistanceLostCheck() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x68
    int* mLynelAIFlags_a{};
};

}  // namespace uking::ai

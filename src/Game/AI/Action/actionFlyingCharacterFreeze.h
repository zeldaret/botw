#pragma once

#include "Game/AI/Action/actionFlyingCharacterReaction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FlyingCharacterFreeze : public FlyingCharacterReaction {
    SEAD_RTTI_OVERRIDE(FlyingCharacterFreeze, FlyingCharacterReaction)
public:
    explicit FlyingCharacterFreeze(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x70
    const float* mStopTime_s{};
};

}  // namespace uking::action

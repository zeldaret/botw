#pragma once

#include "Game/Actor/Action/actionFlyingCharacterFreeFallBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FlyingCharacterFreeze : public FlyingCharacterFreeFallBase {
    SEAD_RTTI_OVERRIDE(FlyingCharacterFreeze, FlyingCharacterFreeFallBase)
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

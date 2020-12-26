#pragma once

#include "Game/AI/Action/actionFlyingCharacterFreeFall.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FlyingCharacterFreeFallEx : public FlyingCharacterFreeFall {
    SEAD_RTTI_OVERRIDE(FlyingCharacterFreeFallEx, FlyingCharacterFreeFall)
public:
    explicit FlyingCharacterFreeFallEx(const InitArg& arg);
    ~FlyingCharacterFreeFallEx() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x70
    const float* mGravityScaleRate_s{};
};

}  // namespace uking::action

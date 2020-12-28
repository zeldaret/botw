#pragma once

#include "Game/AI/Action/actionArrowShootMove.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ArrowShootMoveForLargeObject : public ArrowShootMove {
    SEAD_RTTI_OVERRIDE(ArrowShootMoveForLargeObject, ArrowShootMove)
public:
    explicit ArrowShootMoveForLargeObject(const InitArg& arg);
    ~ArrowShootMoveForLargeObject() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x150
    const float* mRayCastDist_s{};
    // static_param at offset 0x158
    sead::SafeString mCallSEKeyAtStick_s{};
    // dynamic_param at offset 0x168
    bool* mIsReInitShoot_d{};
};

}  // namespace uking::action

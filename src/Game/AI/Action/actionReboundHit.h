#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ReboundHit : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ReboundHit, ksys::act::ai::Action)
public:
    explicit ReboundHit(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // static_param at offset 0x20
    const float* mSpeed_s{};
    // static_param at offset 0x28
    const float* mGravityRate_s{};
};

}  // namespace uking::action

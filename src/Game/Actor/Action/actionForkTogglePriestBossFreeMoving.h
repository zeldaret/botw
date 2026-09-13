#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkTogglePriestBossFreeMoving : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkTogglePriestBossFreeMoving, ksys::act::ai::Action)
public:
    explicit ForkTogglePriestBossFreeMoving(const InitArg& arg);
    ~ForkTogglePriestBossFreeMoving() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // static_param at offset 0x20
    const bool* mSetFreeMoving_s{};
};

}  // namespace uking::action

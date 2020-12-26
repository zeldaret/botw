#pragma once

#include "Game/AI/Action/actionSwarmDamaged.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SwarmChemicalDamaged : public SwarmDamaged {
    SEAD_RTTI_OVERRIDE(SwarmChemicalDamaged, SwarmDamaged)
public:
    explicit SwarmChemicalDamaged(const InitArg& arg);
    ~SwarmChemicalDamaged() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x1c0
    const float* mResetChemicalTimer_s{};
    // static_param at offset 0x1c8
    const bool* mIsResetAllObject_s{};
};

}  // namespace uking::action
